// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#pragma once

#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
using namespace std;

bool fileExists (const string& name);

bool isFileEmpty(ifstream& file);

bool processFilteredDomains(ifstream& file, set<string>& filteredDomains);