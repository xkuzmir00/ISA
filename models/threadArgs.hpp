// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#pragma once
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include "arguments.hpp"
#include "../constants.hpp"
#include <pthread.h>

struct ThreadArgs {
    int sock;
    sockaddr_storage clientAddr;
    socklen_t clientAddrLen;
    char* queryBuffer;
    ssize_t querySize;
    Arguments* args;
    sockaddr_storage forwardAddrStorage;
    socklen_t forwardAddrLen;
};

ThreadArgs* prepareThreadArgs(int sock, const sockaddr_storage& clientAddr, socklen_t clientAddrLen,
                             const char* buffer, ssize_t bufferLen, Arguments* arguments);

void* handleQuery(void* arg);