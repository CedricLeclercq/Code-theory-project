#ifndef CODE_THEORY_ADFGVX_H
#define CODE_THEORY_ADFGVX_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>

class adfgvx {

public:
    std::string encode(std::string message, std::string secret_alphabet1, std::string keyword);

    std::string decode(std::string message, std::string secret_alphabet1, std::string keyword);
};


#endif //CODE_THEORY_ADFGVX_H
