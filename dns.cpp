// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

using namespace std;
#include <iostream>
#include "models/arguments.hpp"
#include "utility/argumentParser.hpp"

int main(int argc, char* argv[]) {
    Arguments args("", "53", "");

    if(!parseArguments(argc, argv, &args)){
        return 1;
    }

    return 0;
}