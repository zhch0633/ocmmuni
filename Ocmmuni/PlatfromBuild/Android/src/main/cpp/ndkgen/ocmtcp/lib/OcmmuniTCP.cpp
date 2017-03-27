//
// Created by zhch0633 on 16/03/17.
//
#include "OcmmuniTCP.h"

void HelloFunc(){
    printf("Hello ocmmuni tcp\n");
    TestSocket();
}

void TestSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int err = errno;
}