// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include "argumentParser.hpp"
#include "../models/arguments.hpp"

bool parseArguments(int argc, char* argv[], Arguments* args){
    if(!isArgLengthValid(argc)){
        return false;
    }

    vector<string> arguments = argvToStrings(argc, argv);
    set<string> seenArguments;

    int i = 1;
    while(i < argc){
        string currentArg = arguments.at(i);
        if(isCurrentArgumentLast(argc, i, currentArg)){
            return false;
        }

        if (seenArguments.find(currentArg) != seenArguments.end()) {
            cerr << "Duplicate argument: " << currentArg << ".\n";
            return false;
        }
        seenArguments.insert(currentArg);

        string argValue = arguments.at(i + 1);
        if(argValue == ""){
            cerr << "Value for the argument " << currentArg << " is empty.\n";
            return false;
        }

        if(currentArg == "-s"){
            if(!processServerArgument(argValue, args)){
                return false;
            }
        }
        else if(currentArg == "-p"){
            if(!processPortArgument(argValue, args)){
                return false;
            }
        }
        else if(currentArg == "-f"){
            if(!processFilterArgument(argValue, args)){
                return false;
            }
        }
        else {
            cerr << "Invalid argument type " << currentArg << ".\n";
            return false;
        }

        i = i+2;
    }

    if(!(seenArguments.find("-s") != seenArguments.end()) || !(seenArguments.find("-f") != seenArguments.end())){
        cerr << "Missing server or filename argument.\n";
        return false;
    }

    return true;
}

bool isArgLengthValid(int argc){
    if(argc != 5 && argc != 7){
        cerr << "Incorrect argument count.\n";
        return false;
    }

    return true;
}

bool isCurrentArgumentLast(int argc, int i, string &arg){
    if(argc-1 == i){
        cerr << "Invalid argument " << arg << ", no argument value entered.\n";
        return true;
    }

    return false;
}

bool processServerArgument(string& argument, Arguments* args) {
    return setupForwardAddress(*args, argument);
}

bool processPortArgument(string &argument, Arguments* args){
    if(argument.at(0) == '-' || argument == "0"){
        cerr << "Port has to be a positive integer value.\n";
        return false;
    }

    int convertedPort = convertStringToInt(argument);
    if(convertedPort == -1){
        return false;
    }

    if(convertedPort > 65535){
        cerr << "Entered port is out of bounds (1 - 65535).\n";
        return false;
    }

    args->listenPort = convertedPort;
    return true;
}

bool processFilterArgument(string &argument, Arguments* args){
    if(!fileExists(argument)){
        cerr << "Entered file '" << argument << "' doesn't exist.\n";
        return false; 
    }

    args->fileName = argument;
    return true;
}