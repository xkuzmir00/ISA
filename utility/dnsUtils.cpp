#include "dnsUtils.hpp"
#include "../constants.hpp"

int getQuestionSectionLength(const char* buffer, ssize_t size) {
    int pos = headerLength;
    while (pos < size && buffer[pos] != 0) {
        unsigned char len = buffer[pos];
        pos += len + 1;
        if (pos >= size) return -1;
    }
    if (pos + 1 + 4 > size) return -1;
    return (pos + 1 + 4) - headerLength;
}

bool isDomainFiltered(const string& queryDomain, const set<string>& filteredDomains) {
    string domain = queryDomain;

    while (!domain.empty()) {
        if (filteredDomains.count(domain) > 0) {
            return true;
        }
        
        size_t dotPos = domain.find('.');
        if (dotPos == string::npos) {
            break;
        }
        
        domain = domain.substr(dotPos + 1);
    }
    return false;
}

void sendRefusedResponse(int sock, const sockaddr_storage& clientAddress, socklen_t clientLen, const char* originalQuery, ssize_t originalQueryLen) {
    char response[messageBufferLength] = {0};
    DNSHeader* header = (DNSHeader*)response;
    uint16_t transactionID = (uint16_t(static_cast<unsigned char>(originalQuery[0])) << 8) | uint16_t(static_cast<unsigned char>(originalQuery[1]));

    header->id = htons(transactionID);
    uint16_t flags = (1 << 15);
    flags |= (originalQuery[2] & DNSReponse) << 8;
    flags |= RCODE;
    header->flags = htons(flags);

    header->qdcount = htons(1);
    header->ancount = 0;
    header->nscount = 0;
    header->arcount = 0;

    int questionLen = getQuestionSectionLength(originalQuery, originalQueryLen);
    if (questionLen < 0) {
        cerr << "Malformed DNS query: unable to determine question length\n";
        return;
    }

    memcpy(response + sizeof(DNSHeader), originalQuery + headerLength, questionLen);

    ssize_t sent = sendto(sock, response, sizeof(DNSHeader) + questionLen, 0, (const sockaddr*)&clientAddress, clientLen);
    if (sent < 0) {
        cerr << "Sendto failed: " << strerror(errno) << "\n";
    }
}