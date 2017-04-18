//
// Created by zhch0633 on 16/03/17.
//

#ifndef OCMTCP
#define OCMTCP
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <boost/system/error_code.hpp>

void HelloFunc();
void SayHello(const boost::system::error_code&);
void TestSocket();
#endif
