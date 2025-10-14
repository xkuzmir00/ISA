// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

using namespace std;
#include <iostream>
#include "models/arguments.hpp"
#include "utility/argumentParser.hpp"
#include "utility/fileUtils.hpp"

void display(set<string> s)
{
    set<string>::iterator itr;
    
    for (itr = s.begin(); 
        itr != s.end(); itr++) 
    {
        cout << *itr << " \n";
    }
}  

int main(int argc, char* argv[]) {
    Arguments args("", "53", "");

    if(!parseArguments(argc, argv, &args)){
        return 1;
    }
    
    ifstream file(args.fileName);
    if(!file) {
        cout << "An error occured while opening " << args.fileName << ".\n";
        return 1;
    }

    if(isFileEmpty(file)){
        cout << "The entered file is empty.\n";
        return 1;
    }

    set<string> filteredDomains;
    if(!processFilteredDomains(file, filteredDomains)){
        return 1;
    }

    return 0;
}