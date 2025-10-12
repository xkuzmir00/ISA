// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#pragma once

using namespace std;
#include <string>

class Arguments {
    public:
        string address;
        string port;
        string fileName;
        Arguments(string address, string port, string fileName);
};