#include <string>
#include <sstream>

#include "playfair.h"

using namespace std;

int indexof(const std::string& text, char& pattern) {
    std::string::size_type loc = text.find(pattern, 0);
    return (loc != std::string::npos) ? loc : -1;
}

void transform(const string &config, char &c1, char &c2, int sign) {
    int index1 = indexof(config, c1);
    int index2 = indexof(config, c2);
    assert(index1 != -1 && index2 != -1);
    int row1 = index1/5, col1 = index1%5;
    int row2 = index2/5, col2 = index2%5;
    assert(!(row1 == row2 && col1 == col2));
    if (row1 == row2) {
        col1 = (col1+sign)%5;
        col2 = (col2+sign)%5;
    } else if (col1 == col2) {
        row1 = (row1+sign)%5;
        row2 = (row2+sign)%5;
    } else {
        int tempcol = col1;
        col1 = col2;
        col2 = tempcol;
    }
    c1 = config.at(row1*5+col1);
    c2 = config.at(row2*5+col2);
}

void encode(const string &config, char &c1, char &c2) {
    transform(config, c1, c2, 1);
}

void decode(const string &config, char &c1, char &c2) {
    transform(config, c1, c2, -1);
}

string encrypt(string text, const string &key) {
    text.erase(std::remove_if(text.begin(), text.end(), ::isspace),text.end());
    stringstream encrypted;
    bool digram = false;
    char c1, c2;
    for (char const &c: text) {
        if (!digram) {
            c1 = c;
            digram = true;
        } else {
            if (c1 == c) {
                c2 = 'x';
                encode(key, c1, c2);
                encrypted << c1 << c2;
                c1 = c;
            } else {
                c2 = c;
                digram = false;
                encode(key, c1, c2);
                encrypted << c1 << c2;
            }
        }
    }
    return encrypted.str();
}

void decrypt(const string &text, vector<string> &dutch, vector<string> &english, vector<string> &french, vector<string> &german, vector<string> &spanish) {
    // Step 1: permutate

}