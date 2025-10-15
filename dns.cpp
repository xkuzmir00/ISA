// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

using namespace std;
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "models/arguments.hpp"
#include "utility/argumentParser.hpp"
#include "utility/fileUtils.hpp"
#include "utility/socketUtils.hpp"

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
    Arguments args("", 53, "");

    if(!parseArguments(argc, argv, &args)){
        return 1;
    }
    
    ifstream file(args.fileName);
    if(!file) {
        cerr << "An error occured while opening " << args.fileName << ".\n";
        return 1;
    }

    if(isFileEmpty(file)){
        cerr << "The entered file is empty.\n";
        return 1;
    }

    set<string> filteredDomains;
    if(!processFilteredDomains(file, filteredDomains)){
        return 1;
    }

    int sock = setUpSocket(args.port);
    if(sock < 0){
        return 1;
    }
    
    while (true) {
        char messageBuffer[512];
        sockaddr_storage cliaddress;
        socklen_t len = sizeof(cliaddress);

        ssize_t n = recvfrom(sock, messageBuffer, sizeof(messageBuffer), 0, (struct sockaddr*)&cliaddress, &len);
        if (n < 0) {
            continue;
        }

        char clientIP[INET6_ADDRSTRLEN] = {0};

        if (cliaddress.ss_family == AF_INET) {
            sockaddr_in *addr_in = (sockaddr_in *)&cliaddress;
            inet_ntop(AF_INET, &(addr_in->sin_addr), clientIP, sizeof(clientIP));
        } else if (cliaddress.ss_family == AF_INET6) {
            sockaddr_in6 *addr_in6 = (sockaddr_in6 *)&cliaddress;
            inet_ntop(AF_INET6, &(addr_in6->sin6_addr), clientIP, sizeof(clientIP));
        }

        cout << "Data received: ";
        for (ssize_t i = 0; i < n; ++i) {
            char c = messageBuffer[i];
            if (isprint(static_cast<unsigned char>(c))) {
                cout << c;
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }

    close(sock);
    return 0;
}