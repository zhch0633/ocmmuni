#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;

//定义了一个发送队列
typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
private:
    boost::asio::io_service& io_service_;
    tcp::socket socket_;
    chat_message read_msg_;
    chat_message_queue write_msgs_;

public:
    chat_client(boost::asio::io_service& io_service,
                tcp::resolver::iterator endpoint_iterator)
            : io_service_(io_service), socket_(io_service) {

        //构造函数时期即对连接成功进行回调注册
        boost::asio::async_connect(socket_, endpoint_iterator,
                                   boost::bind(&chat_client::handle_connect, this,
                                               boost::asio::placeholders::error));
    }

    void write(const chat_message& msg) {
        //Post向队列中投递任务，然后激活空闲线程执行任务。
        io_service_.post(boost::bind(&chat_client::do_write, this, msg));
    }

    void close() {
        io_service_.post(boost::bind(&chat_client::do_close, this));
    }

private:

    /**
    * 连接处理函数，一旦连接上来，直接会调用此函数
    */
    void handle_connect(const boost::system::error_code& error) {
        if (!error) {
            //先保证读取足够整个头部，read_msg_.data()实质上是返回一个分配了缓冲的char *指针。
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.data(), chat_message::header_length),
                    //注册连接成功后，回调handle_read_header()函数
                                    boost::bind(&chat_client::handle_read_header, this,
                                                boost::asio::placeholders::error));
        }
    }

    /**
    * 连接成功后，调用此函数读取头部信息
    */
    void handle_read_header(const boost::system::error_code& error) {
        if (!error && read_msg_.decode_header()) {
            //然后读取剩余的包体长度，并注册读取包体的函数，read_msg_.body()实际上是返回了一个同样分配了缓冲的char *指针
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                    //注册读取头部完成后，回调handle_read_body函数
                                    boost::bind(&chat_client::handle_read_body, this,
                                                boost::asio::placeholders::error));
        } else {
            //出现错误则关闭
            do_close();
        }
    }
    void handle_read_body(const boost::system::error_code& error) {
        if (!error) {
            //注意，这2句就是收到包之后直接显示内容，这里应该替换你所需要的解包逻辑及包处理逻辑2部分。
            std::cout.write(read_msg_.body(), read_msg_.body_length());
            std::cout << "\n";
            //回调完毕后，再次注册读取头部函数，这是必须的，保证每次处理完之后，重新注册读取头部函数
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.data(), chat_message::header_length),
                                    boost::bind(&chat_client::handle_read_header, this,
                                                boost::asio::placeholders::error));
        } else {
            do_close();        }
    }


    void do_write(chat_message msg) {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress) {
            //把队列为空作为发送完成的标记，以保证发送出错的时候，还能按发送顺序进行
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(write_msgs_.front().data(),
                                                         write_msgs_.front().length()),
                                     boost::bind(&chat_client::handle_write, this,
                                                 boost::asio::placeholders::error));
        }
    }

    void handle_write(const boost::system::error_code& error) {
        if (!error) {
            write_msgs_.pop_front();
            if (!write_msgs_.empty()) {
                //注册回调，若有问题会在error 上返回，一旦出错就会断开连接
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(write_msgs_.front().data(),
                                                             write_msgs_.front().length()),
                                         boost::bind(&chat_client::handle_write, this,
                                                     boost::asio::placeholders::error));
            } else {

            }
        } else {
            do_close();
        }
    }

    void do_close() {
        socket_.close();
    }

};
int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        //定义io_service，可以把它看作是socket类
        boost::asio::io_service io_service;

        //provides the ability to resolve a query to a list of endpoints.
        tcp::resolver resolver(io_service);
        //The ip::basic_resolver_query class template
        tcp::resolver::query query(argv[1], argv[2]);
        //An iterator over the entries produced by a resolver.
        tcp::resolver::iterator iterator = resolver.resolve(query);

        //初始化一个对象c，作为client的实例
        chat_client c(io_service, iterator);

        //生成线程对象t, 绑定在io_service::run方法中, 把io_service作为桥梁在2个进程间进行通讯
        //目的是用另外一个线程对socket进行非阻塞回调的接收及处理，不影响主线程操作。
        boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

        char line[chat_message::max_body_length + 1];
        //注意，下面的while循环则应该是程序的主循环，也应该封装成一个函数供调用为好
        while (std::cin.getline(line, chat_message::max_body_length + 1)) {
            using namespace std; // For strlen and memcpy.
            chat_message msg;
            msg.body_length(strlen(line));
            memcpy(msg.body(), line, msg.body_length());
            //构造包头（主要是长度，这是最简单实用的方法）
            msg.encode_header();
            //直接写入数据到socket
            c.write(msg);
        }

        c.close();
        t.join();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}