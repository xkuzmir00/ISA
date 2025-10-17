// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include "threadArgs.hpp"

ThreadArgs* prepareThreadArgs(int sock, const sockaddr_storage& clientAddr, socklen_t clientAddrLen,
                             const char* buffer, ssize_t bufferLen, Arguments* arguments)
{
    ThreadArgs* args = new ThreadArgs;
    if (!args) return nullptr;

    args->sock = sock;
    args->clientAddr = clientAddr;
    args->clientAddrLen = clientAddrLen;

    args->querySize = bufferLen;
    args->args = arguments;

    args->queryBuffer = new char[bufferLen];
    if (!args->queryBuffer) {
        delete args;
        return nullptr;
    }

    memcpy(args->queryBuffer, buffer, bufferLen);

    args->forwardAddrStorage = arguments->forwardAddr;
    args->forwardAddrLen = arguments->forwardAddrLen;

    return args;
}

void* handleQuery(void* arg) {
    ThreadArgs* targs = (ThreadArgs*)arg;

    if (sendto(targs->sock, targs->queryBuffer, targs->querySize, 0,
               (struct sockaddr*)&targs->forwardAddrStorage, targs->forwardAddrLen) < 0) {
        std::cerr << "Failed to send to forward resolver: " << strerror(errno) << "\n";
        delete[] targs->queryBuffer;
        delete targs;
        return nullptr;
    }

    char responseBuffer[messageBufferLength];
    sockaddr_storage forwardAddr;
    socklen_t forwardLen = sizeof(forwardAddr);

    ssize_t respLen = recvfrom(targs->sock, responseBuffer, sizeof(responseBuffer), 0,
                               (struct sockaddr*)&forwardAddr, &forwardLen);
    if (respLen < 0) {
        std::cerr << "Failed to receive forward response: " << strerror(errno) << "\n";
        delete[] targs->queryBuffer;
        delete targs;
        return nullptr;
    }

    ssize_t sent = sendto(targs->sock, responseBuffer, respLen, 0,
                          (struct sockaddr*)&targs->clientAddr, targs->clientAddrLen);
    if (sent < 0) {
        std::cerr << "Failed to send response to client: " << strerror(errno) << "\n";
    }

    delete[] targs->queryBuffer;
    delete targs;
    return nullptr;
}