// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include "fileUtils.hpp"
#include "stringUtils.hpp"
#include "addressUtils.hpp"

bool fileExists (const string& name){
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0); 
}

bool isFileEmpty(ifstream& file) {
    return file.peek() == ifstream::traits_type::eof();
}

bool processFilteredDomains(ifstream& file, set<string>& filteredDomains){
    string line;
    try{
        while(getline(file, line)){
            line = trim(line);
            if(line.empty() || line.at(0) == '#'){
                continue;
            }

            if (containsInvalidChars(line)) {
                cerr << "Warning: domain \"" << line << "\" contains invalid characters and will be skipped.\n";
                continue;
            }

            filteredDomains.insert(line);
        }
    }catch(int errorCode) {
        cerr << "An error has occured while processing the list of domains. Error code: " << errorCode << "\n";
        return false;
    }

    if(filteredDomains.size() < 1){
        cerr << "The list of domains to filter is empty.\n";
        return false;
    }

    return true;
}