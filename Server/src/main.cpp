#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

using namespace std;

void print1(const boost::system::error_code& /*e*/,
            boost::asio::deadline_timer* t, int* count)
{
    if (*count < 5)
    {
        cout << *count << "\n" << endl;
        ++(*count);

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));

        t->async_wait(boost::bind(print1, boost::asio::placeholders::error, t, count));
    }

}

void tuttimer3()
{
    boost::asio::io_service io;
    int count = 0;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));

    t.async_wait(boost::bind(print1, boost::asio::placeholders::error, &t, &count));

    io.run();

    cout << "Final count is " << count << "\n" << endl;
}

int main() {
    
    tuttimer3();
    return 0;
}