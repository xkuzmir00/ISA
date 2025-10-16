// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

using namespace std;
#include <string>
#include "arguments.hpp"

Arguments::Arguments(int port, const std::string& fileName)
    : resolverAddr(nullptr), port(port), fileName(fileName) {}

Arguments::~Arguments() {
    if (resolverAddr != nullptr) {
        freeaddrinfo(resolverAddr);
        resolverAddr = nullptr;
    }
}