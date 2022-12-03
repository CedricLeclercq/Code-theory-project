//
// Created by Cédric Leclercq on 31/10/2022.
//

#ifndef CODE_THEORY_UTILITIES_H
#define CODE_THEORY_UTILITIES_H
#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <map>

using namespace std;

class Utilities {
public:
    Utilities();

    tuple< map< string, string >, string> ReadContents(const string &inputfile);
    static std::vector<std::string> convertToPermutation(std::string dom, std::string ran);

    // In-place rotates s towards left by d
    static void left_rotate(string &s, int d);

    // In-place rotates s towards right by d
    void right_rotate(string &s, int d);
};


#endif //CODE_THEORY_UTILITIES_H
