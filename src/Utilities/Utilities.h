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
    static void leftRotate(string &s, int d);

    // Follow permutation
    static char followPermutation(const std::vector<std::string>& perm, const char& ch);

    // In-place rotates s towards right by d
    void rightRotate(string &s, int d);

    // Get alphabet
    static std::string getAlphabet() {return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";}

    static char cyclometric_continuation(const std::string& dom,const char& ch, int k);

    static char InverseFollowPermutation(const vector<std::string> &perm, const char& ch);

    static std::vector<std::vector<int>> createEnigmaRotorPermutations(std::vector<int> all_rotors);
};


#endif //CODE_THEORY_UTILITIES_H
