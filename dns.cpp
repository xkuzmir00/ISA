// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

using namespace std;
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "constants.hpp"
#include "models/arguments.hpp"
#include "utility/argumentParser.hpp"
#include "utility/fileUtils.hpp"
#include "utility/socketUtils.hpp"
#include "utility/addressUtils.hpp"
#include "utility/dnsUtils.hpp"

int main(int argc, char* argv[]) {
    Arguments args(defaultPort, "");

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
        char messageBuffer[messageBufferLength];
        sockaddr_storage cliaddress;
        socklen_t len = sizeof(cliaddress);

        ssize_t num = recvfrom(sock, messageBuffer, sizeof(messageBuffer), 0, (struct sockaddr*) &cliaddress, &len);
        if (num < 0) {
            continue;
        }

        char clientIP[INET6_ADDRSTRLEN] = {0};

        if (cliaddress.ss_family == AF_INET) {
            sockaddr_in *addr_in = (sockaddr_in *) &cliaddress;
            inet_ntop(AF_INET, &(addr_in->sin_addr), clientIP, sizeof(clientIP));
        } else if (cliaddress.ss_family == AF_INET6) {
            sockaddr_in6 *addr_in6 = (sockaddr_in6 *) &cliaddress;
            inet_ntop(AF_INET6, &(addr_in6->sin6_addr), clientIP, sizeof(clientIP));
        }

        string domainName;
        uint16_t queryType;

        if (parseDNSQuery(messageBuffer, num, domainName, queryType)) {
            if(queryType != typeADNS){
                sendRefusedResponse(sock, cliaddress, len, messageBuffer, num);
                continue;
            }

            if(isDomainFiltered(domainName, filteredDomains)) {
                sendRefusedResponse(sock, cliaddress, len, messageBuffer, num);
                continue;
            }

            
        } else {
            cout << "Failed to parse DNS query.\n";
        }
    }

    close(sock);
    return 0;
}