// Author: Richard Kuzmisin
// Login: xkuzmir00 (260077)

#include "integerUtils.hpp"

int convertStringToInt(string num){
    try
    {
        return stoi(num);
    }
    catch(const exception& e)
    {
        cout << "Value " << num << " is not valid integer value.\n";
        return -1;
    }
}