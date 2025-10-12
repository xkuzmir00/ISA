// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include "stringUtils.hpp"
#include <iostream>

vector<string> argvToStrings(int argc, char* argv[]){
    vector<string> strings;
    for(int i = 0; i < argc; ++i){
        strings.push_back(trim(string(argv[i])));
    }

    return strings;
}

string trim(const string &s){
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    size_t end = s.find_last_not_of(" \t\n\r\f\v");

    if(start == string::npos){
        return "";
    }

    return s.substr(start, end-start+1);
}