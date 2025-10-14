// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
using namespace std;

bool fileExists (const std::string& name);

bool isFileEmpty(std::ifstream& file);

bool processFilteredDomains(ifstream& file, set<string>& filteredDomains);