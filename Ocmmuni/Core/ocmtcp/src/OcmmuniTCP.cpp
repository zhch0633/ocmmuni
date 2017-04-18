//
// Created by zhch0633 on 16/03/17.
//
#include "OcmmuniTCP.h"
#include <sys/socket.h>
#include <iostream>
#include <asio.hpp>

using namespace asio;

void HelloFunc(){
    asio::io_service io;
    asio::deadline_timer t(io, boost::posix_time::seconds(5));
    t.wait();

    std::cout << "Hello ASIO" << std::endl;
}

void TestSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int err = errno;
}
