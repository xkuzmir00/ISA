// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#pragma once

using namespace std;
#include <string>

class Arguments {
    public:
        string address;
        int port;
        string fileName;
        Arguments(string address, int port, string fileName);
};