// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#pragma once

using namespace std;
#include <string>
#include <netdb.h>

class Arguments {
    public:
        struct addrinfo* resolverAddr;
        int port;
        string fileName;
        Arguments(int port, const string& fileName);;
        ~Arguments();
};