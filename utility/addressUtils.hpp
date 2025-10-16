// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#pragma once

#include <string>
#include <cstdint>
using namespace std;

bool containsInvalidChars(const string& domain);

bool parseDNSQuery(const char* buffer, ssize_t size, string& domainName, uint16_t& queryType);