// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include "arguments.hpp"

Arguments::Arguments(int listenPort, int forwardPort, const string& fileName)
    : listenPort(listenPort),
      forwardPort(forwardPort),
      fileName(fileName),
      forwardAddrLen(0)
{ }

bool setupForwardAddress(Arguments& args, string& serverName) {
    struct addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    struct addrinfo* res = nullptr;
    int ret = getaddrinfo(serverName.c_str(), nullptr, &hints, &res);
    if (ret != 0) {
        cerr << "Failed to resolve " << serverName << ": " << gai_strerror(ret) << endl;
        return false;
    }

    memcpy(&args.forwardAddr, res->ai_addr, res->ai_addrlen);
    args.forwardAddrLen = res->ai_addrlen;

    if (args.forwardAddr.ss_family == AF_INET) {
        ((struct sockaddr_in*)&args.forwardAddr)->sin_port = htons(args.forwardPort);
    } else if (args.forwardAddr.ss_family == AF_INET6) {
        ((struct sockaddr_in6*)&args.forwardAddr)->sin6_port = htons(args.forwardPort);
    } else {
        cerr << "Unknown address family for forward resolver" << endl;
        freeaddrinfo(res);
        return false;
    }

    freeaddrinfo(res);
    return true;
}