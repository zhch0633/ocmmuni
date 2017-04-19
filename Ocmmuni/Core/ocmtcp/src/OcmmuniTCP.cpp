//
// Created by zhch0633 on 16/03/17.
//
#include "OcmmuniTCP.h"
#include <iostream>
#include <asio.hpp>
#include "server.hpp"

#include "asio.hpp"
#include <string>

using namespace asio;

void HelloFunc(){
    std::cout << "start server";

    try
    {
        // Check command line arguments.
        std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
        std::cerr << "  For IPv4, try:\n";
        std::cerr << "    receiver 0.0.0.0 80 .\n";
        std::cerr << "  For IPv6, try:\n";
        std::cerr << "    receiver 0::0 80 .\n";

        // Initialise the server.
        http::server::server s("0.0.0.0", "80", "..");

        // Run the server until stopped.
        s.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << "\n";
    }

}

void TestSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int err = errno;
}
