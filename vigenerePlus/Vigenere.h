#ifndef VIGENEREPLUS_VIGENERE_H
#define VIGENEREPLUS_VIGENERE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

class Vigenere {
public:
    Vigenere(const string &key);

    string encrypt(const string &Plaintext);

    string decrypt(const string &Ciphertext);


private:
    vector<vector<char>> vigenere_square;
    string key;
    map<char, int> alphabet{{'A', 0},
                              {'B', 1},
                              {'C', 2},
                              {'D', 3},
                              {'E', 4},
                              {'F', 5},
                              {'G', 6},
                              {'H', 7},
                              {'I', 8},
                              {'J', 9},
                              {'K', 10},
                              {'L', 11},
                              {'M', 12},
                              {'N', 13},
                              {'O', 14},
                              {'P', 15},
                              {'Q', 16},
                              {'R', 17},
                              {'S', 18},
                              {'T', 19},
                              {'U', 20},
                              {'V', 21},
                              {'W', 22},
                              {'X', 23},
                              {'Y', 24},
                              {'Z', 25}};
};


#endif //VIGENEREPLUS_VIGENERE_H
