#include <iostream>
#include <string>
#include <sstream>
#include "Vigenere.h"

using namespace std;

int main() {
    Vigenere Code = Vigenere("PYRAMID");
    std::cout << Code.encrypt("attackatsundown") << std::endl;
    std::cout << Code.decrypt("prkaosdiqlnpwzc") << std::endl;
    return 0;
}
