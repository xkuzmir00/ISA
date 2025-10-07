using namespace std;
#include <string>
#include "arguments.h"

Arguments::Arguments(string address, string port, string fileName){
    this->address = address;
    this->port = port;
    this->fileName = fileName;
}