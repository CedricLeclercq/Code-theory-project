#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

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
        col1 = (col1+sign+5)%5;
        col2 = (col2+sign+5)%5;
    } else if (col1 == col2) {
        row1 = (row1+sign+5)%5;
        row2 = (row2+sign+5)%5;
    } else {
        int tempcol = col1;
        col1 = col2;
        col2 = tempcol;
    }
    index1 = row1*5+col1;
    index2 = row2*5+col2;
    c1 = config.at(index1);
    c2 = config.at(index2);
}

void encode(const string &config, char &c1, char &c2) {
    transform(config, c1, c2, 1);
}

void decode(const string &config, char &c1, char &c2) {
    transform(config, c1, c2, -1);
}

void encode(const string &config, const string& input, stringstream &encoded) {
    bool digram = false;
    char c1, c2;
    for (char const &c: input) {
        if (!digram) {
            c1 = c;
            digram = true;
        } else {
            if (c1 == c) {
                c2 = 'x';
                encode(config, c1, c2);
                encoded << c1 << c2;
                c1 = c;
            } else {
                c2 = c;
                digram = false;
                encode(config, c1, c2);
                encoded << c1 << c2;
            }
        }
    }
}

void decode(const string &config, const string& input, stringstream &decoded) {
    bool digram = false, potential_double = false;
    char c1, c2, doubled;
    for (char const &c: input) {
        if (!digram) {
            c1 = c;
            digram = true;
        } else {
            c2 = c;
            digram = false;
            decode(config, c1, c2);
            if (potential_double) {
                if(c1 == doubled) {
                    decoded << c1;
                } else {
                    decoded << c1 << 'x';
                }
            }
            if (c2 == 'x') {
                doubled = c1;
                potential_double = true;
            } else {
                decoded << c1 << c2;
            }
        }
    }
}

string encrypt(string text, const string &key) {
    text.erase(std::remove_if(text.begin(), text.end(), ::isspace),text.end());
    stringstream encrypted;
    encode(key, text, encrypted);
    return encrypted.str();
}

std::map<char, double> occurences = {
        {'e', 0.1891},
        {'n', 0.1003},
        {'a', 0.0749},
        {'t', 0.0679},
        {'i', 0.0796},
        {'r', 0.0641},
        {'o', 0.0606},
        {'d', 0.0593},
        {'s', 0.0373},
        {'l', 0.0357},
        {'g', 0.0340},
        {'v', 0.0285},
        {'h', 0.0238},
        {'k', 0.0225},
        {'m', 0.0221},
        {'u', 0.0199},
        {'b', 0.0158},
        {'p', 0.0157},
        {'w', 0.0152},
        {'z', 0.0139},
        {'c', 0.0124},
        {'f', 0.0081},
        {'x', 0.0040},
        {'y', 0.0035},
        {'q', 0.0009}
};

void decrypt(const string &text, vector<string> &dutch, vector<string> &english, vector<string> &french, vector<string> &german, vector<string> &spanish) {
    // Step 1: permutate
    std::string config = "abcdefghiklmnopqrstuvwxyz";
    assert(config.length() == 25);
    long counter = 0;
    double best = 10000;
    int textLength = text.length();
    do {
        stringstream decoded;
        decode(config, text, decoded);
        string decoded_str = decoded.str();

//        int count = 0;
//        for (auto& dictionary: {dutch, english, french, german, spanish}) {
//            count = std::count_if(dictionary.begin(), dictionary.end(), [decoded_str](const string &word){
//                return decoded_str.find(word) != string::npos;
//            });
//            if (count > best) {
//                cout << "Better configuration (from " << best << " to " << count << "): " << config << " on " << dictionary.front() << endl;
//                best = count;
//            }
//        }

//        std::map<char, double> charCount;


        double sum = 0;
        for (const char c: "abcdefghiklmnopqrstuvwxyz") {
            double percentage = (double) std::count(decoded_str.begin(), decoded_str.end(), c) / textLength;
            sum += sqrt(pow(occurences[c] - percentage, 2));
        }
        if (sum < best) {
            cout << "Better configuration (from " << best << " to " << sum << "): " << config;
            best = sum;
        }

    } while (std::next_permutation(config.begin(), config.end()) && ++counter < 5001);
    cout << "Last configuration: " << config << endl;
}