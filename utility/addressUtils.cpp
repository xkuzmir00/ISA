// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include "addressUtils.hpp"
#include "../constants.hpp"
using namespace std;

bool containsInvalidChars(const string& domain) {
    for (char ch : domain) {
        if (!(isalnum(ch) || ch == '-' || ch == '.')) {
            return true;
        }
    }
    return false;
}

bool parseDNSQuery(const char* buffer, ssize_t size, string& domainName, uint16_t& queryType) {
    if (size < headerLength) return false;
    
    int pos = headerLength;
    domainName.clear();

    while (pos < size) {
        unsigned char len = buffer[pos];
        if (len == 0) {
            pos++;
            break;
        }

        if (len + pos + 1 > size) return false;
        
        if (!domainName.empty()) domainName += ".";

        domainName.append(buffer + pos + 1, len);
        pos += len + 1;
    }
    
    if (pos + 4 > size) return false;

    queryType = (uint16_t(buffer[pos]) << 8) | uint16_t(buffer[pos + 1]);
    
    return true;
}