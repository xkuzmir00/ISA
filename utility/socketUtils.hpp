// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)
#pragma once
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int setUpSocket(int port);