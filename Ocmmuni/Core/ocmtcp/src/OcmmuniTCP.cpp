//
// Created by zhch0633 on 16/03/17.
//
#include "OcmmuniTCP.h"
#include <sys/socket.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

void HelloFunc(){
    boost::asio::io_service io_service;
    boost::asio::deadline_timer timer(io_service,boost::posix_time::seconds(3));
    int count = 3;
    timer.async_wait(boost::bind(SayHello, _1, &timer, &count));
    io_service.run();
    return;
}

void SayHello(const boost::system::error_code&,
              boost::asio::deadline_timer* timer, int* count) {
    std::cout << "Hello, world!" << std::endl;
    if (--(*count) > 0) {
        timer->expires_at(timer->expires_at() + boost::posix_time::seconds(1));
        timer->async_wait(boost::bind(SayHello, _1, timer, count));
    }
}

void TestSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int err = errno;
}
