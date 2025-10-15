// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include "socketUtils.hpp"

int setUpSocket(int port) {
    int sock = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        cerr << "Socket creation failed: " << strerror(errno) << "\n";
        return -1;
    }

    int off = 0;
    if (setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &off, sizeof(off)) < 0) {
        cerr << "Failed to set socket options: " << strerror(errno) << "\n";
        close(sock);
        return -1;
    }

    sockaddr_in6 servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_addr = in6addr_any;
    servaddr.sin6_port = htons(port);

    if (bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        cerr << "Bind failed on port " << port << ": " << strerror(errno) << "\n";
        close(sock);
        return -1;
    }

    return sock;
}