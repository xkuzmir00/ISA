// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#pragma once
#include <sys/socket.h>
#include <cstdint>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <set>

using namespace std;

struct DNSHeader {
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} __attribute__((packed));

int getQuestionSectionLength(const char* buffer, ssize_t size);

bool isDomainFiltered(const string& queryDomain, const set<string>& filteredDomains);

void sendRefusedResponse(int sock, const sockaddr_storage& clientAddress, socklen_t clientLen, const char* originalQuery, ssize_t originalQueryLen);