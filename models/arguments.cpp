// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

using namespace std;
#include <string>
#include "arguments.hpp"

Arguments::Arguments(string address, int port, string fileName){
    this->address = address;
    this->port = port;
    this->fileName = fileName;
}