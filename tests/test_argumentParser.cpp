// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "../utility/argumentParser.hpp"
#include "../models/arguments.hpp"
#include "../constants.hpp"

using namespace std;

void prepareArgv(const vector<string> &args, int &argc, char **&argv) {
    argc = static_cast<int>(args.size());
    argv = new char*[argc];
    for (int i = 0; i < argc; ++i) {
        argv[i] = strdup(args[i].c_str());
    }
}

void freeArgv(int argc, char **argv) {
    for (int i = 0; i < argc; ++i) {
        free(argv[i]);
    }
    delete[] argv;
}

bool runTest(const string &testName, const vector<string> &arguments, bool expected) {
    int argc;
    char **argv;
    prepareArgv(arguments, argc, argv);
    Arguments args(defaultPort, "");
    bool result = parseArguments(argc, argv, &args);
    freeArgv(argc, argv);

    if (result == expected) {
        cout << "[PASS] " << testName << endl;
        return true;
    } else {
        cout << "[FAIL] " << testName << " Expected " << expected << " but got " << result << endl;
        return false;
    }
}

int main() {
    int fails = 0;

    fails += !runTest("Valid args with default port",
                      {"dns", "-s", "8.8.8.8", "-f", "tests/filter.txt"},
                      true);

    fails += !runTest("Valid args with custom port",
                      {"dns", "-s", "8.8.8.8", "-p", "1053", "-f", "tests/filter.txt"},
                      true);

    fails += !runTest("Missing server argument",
                      {"dns", "-p", "1053", "-f", "tests/filter.txt"},
                      false);

    fails += !runTest("Missing filter argument",
                      {"dns", "-s", "8.8.8.8", "-p", "1053"},
                      false);

    fails += !runTest("Duplicate argument",
                      {"dns", "-s", "8.8.8.8", "-s", "9.9.9.9", "-f", "tests/filter.txt"},
                      false);

    fails += !runTest("Invalid port value (zero)",
                      {"dns", "-s", "8.8.8.8", "-p", "0", "-f", "tests/filter.txt"},
                      false);

    fails += !runTest("Invalid port value (too large)",
                      {"dns", "-s", "8.8.8.8", "-p", "70000", "-f", "tests/filter.txt"},
                      false);

    fails += !runTest("Invalid argument flag",
                      {"dns", "-s", "8.8.8.8", "-q", "something", "-f", "tests/filter.txt"},
                      false);

    fails += !runTest("No argument value for last argument",
                      {"dns", "-s", "8.8.8.8", "-f", ""},
                      false);

    if (fails == 0) {
        cout << "All tests passed successfully." << endl;
        return 0;
    } else {
        cout << fails << " test(s) failed." << endl;
        return 1;
    }
}