// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#pragma once
#include "argumentParser.hpp"
#include "stringUtils.hpp"
#include "integerUtils.hpp"
#include "fileUtils.hpp"
#include "../models/arguments.hpp"
#include <iostream>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <set>

using namespace std;

bool parseArguments(int argc, char* argv[], Arguments* args);

bool isArgLengthValid(int argc);

bool isArgFormatValid(int argc, char* argv[]);

bool isCurrentArgumentLast(int argc, int i, string &arg);

bool processServerArgument(string& argument, Arguments* args);

bool processPortArgument(string &argument, Arguments* args);

bool processFilterArgument(string &argument, Arguments* args);