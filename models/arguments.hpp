// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#pragma once

using namespace std;
#include <string>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

class Arguments {
public:
    int listenPort;
    int forwardPort;
    string fileName;

    sockaddr_storage forwardAddr;
    socklen_t forwardAddrLen;

    Arguments(int listenPort, int forwardPort, const string& fileName);
    ~Arguments() = default;
};

bool setupForwardAddress(Arguments& args, string& serverName);