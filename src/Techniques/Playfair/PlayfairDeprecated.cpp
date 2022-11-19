#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <fstream>

#include "PlayfairDeprecated.h"

using namespace std;

void loadCipherText(const string& filename, string& cipherText) {
    ifstream file(filename);
    getline(file, cipherText);
    file.close();
}

void splitIntoVector(vector<string> &v, string &str) {
    stringstream ss(str);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(substr);
    }
}

void loadDictionary(const string& filename, vector<string> &v) {
    string words;
    ifstream dictionary(filename);
    getline(dictionary, words);
    dictionary.close();
    splitIntoVector(v, words);
}

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
            transform(config, c1, c2, -1);
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

std::map<char, double> occurencesDutch = {
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

std::map<char, double> occurencesFrench = {
        {'a', 0.0870},
        {'b', 0.0093},
        {'c', 0.0315},
        {'d', 0.0355},
        {'e', 0.1783},
        {'f', 0.0096},
        {'g', 0.0097},
        {'h', 0.0108},
        {'i', 0.0769},
        {'k', 0.0016},
        {'l', 0.0568},
        {'m', 0.0323},
        {'n', 0.0642},
        {'o', 0.0534},
        {'p', 0.0303},
        {'q', 0.0089},
        {'r', 0.0643},
        {'s', 0.0791},
        {'t', 0.0711},
        {'u', 0.0614},
        {'v', 0.0183},
        {'w', 0.0004},
        {'x', 0.0042},
        {'y', 0.0019},
        {'z', 0.0021}
};

std::map<char, double> occurencesEnglish = {
        {'a', 0.0849},
        {'b', 0.0207},
        {'c', 0.0453},
        {'d', 0.0338},
        {'e', 0.1116},
        {'f', 0.0181},
        {'g', 0.0247},
        {'h', 0.0300},
        {'i', 0.0774},
        {'k', 0.0110},
        {'l', 0.0548},
        {'m', 0.0301},
        {'n', 0.0665},
        {'o', 0.0716},
        {'p', 0.0316},
        {'q', 0.0019},
        {'r', 0.0758},
        {'s', 0.0573},
        {'t', 0.0695},
        {'u', 0.0363},
        {'v', 0.0100},
        {'w', 0.0128},
        {'x', 0.0029},
        {'y', 0.0177},
        {'z', 0.0027}
};

std::map<char, double> occurencesGerman = {
        {'a', 0.0612},
        {'b', 0.0196},
        {'c', 0.0316},
        {'d', 0.0498},
        {'e', 0.1693},
        {'f', 0.0149},
        {'g', 0.0302},
        {'h', 0.0498},
        {'i', 0.0826},
        {'k', 0.0132},
        {'l', 0.0360},
        {'m', 0.0255},
        {'n', 0.1053},
        {'o', 0.0254},
        {'p', 0.0067},
        {'q', 0.0002},
        {'r', 0.0689},
        {'s', 0.0679},
        {'t', 0.0579},
        {'u', 0.0448},
        {'v', 0.0084},
        {'w', 0.0178},
        {'x', 0.0005},
        {'y', 0.0005},
        {'z', 0.0121}
};

std::map<char, double> occurencesSpanish = {
        {'a', 0.1216},
        {'b', 0.0149},
        {'c', 0.0387},
        {'d', 0.0467},
        {'e', 0.1408},
        {'f', 0.0069},
        {'g', 0.0100},
        {'h', 0.0118},
        {'i', 0.0650},
        {'k', 0.0011},
        {'l', 0.0524},
        {'m', 0.0308},
        {'n', 0.0700},
        {'o', 0.0920},
        {'p', 0.0289},
        {'q', 0.0111},
        {'r', 0.0641},
        {'s', 0.0720},
        {'t', 0.0460},
        {'u', 0.0469},
        {'v', 0.0105},
        {'w', 0.0004},
        {'x', 0.0014},
        {'y', 0.0109},
        {'z', 0.0047}
};

double getFrequencyScore(const string& decoded) {
    auto length = (double) decoded.length();
    double score = 0;
    for (const char c: "abcdefghiklmnopqrstuvwxyz") {
        double percentage = (double) std::count(decoded.begin(), decoded.end(), c) / length;
        score += abs(occurencesDutch[c] - percentage);
//        english += abs(occurencesEnglish[c] - percentage);
//        french += abs(occurencesFrench[c] - percentage);
//        german += abs(occurencesGerman[c] - percentage);
//        spanish += abs(occurencesSpanish[c] - percentage);
    }
    return score;
}


void decrypt(const string &text) {
    // Step 1: permutate
    std::string config = "abcdefghiklmnopqrstuvwxyz";
    assert(config.length() == 25);
    long counter = 0;
    double best = 10000;
    long textLength = text.length();
    string bestConfig = "abcdefghiklmnopqrstuvwxyz";
    do {
        stringstream decoded;
        decode(config, text, decoded);
        string decoded_str = decoded.str();

        double dutch = 0, english = 0, french = 0, german = 0, spanish = 0;
        for (const char c: "abcdefghiklmnopqrstuvwxyz") {
            double percentage = (double) std::count(decoded_str.begin(), decoded_str.end(), c) / (double) textLength;
            dutch += abs(occurencesDutch[c] - percentage);
            english += abs(occurencesEnglish[c] - percentage);
            french += abs(occurencesFrench[c] - percentage);
            german += abs(occurencesGerman[c] - percentage);
            spanish += abs(occurencesSpanish[c] - percentage);
        }
        for (const double score: {dutch, english, french, german, spanish}) {
            if (score < best) {
                best = score;
                bestConfig = config;
            }
        }
        if (counter%100000==0) {
            cout << "Current count:         " << counter << endl;
            cout << "Current configuration: " << config << endl;
            cout << "Best configuration:    " << bestConfig << endl;
            cout << "=====================================" << endl;
        }
        counter++;
    } while (std::next_permutation(config.begin(), config.end()));// && ++counter < 100000);
    cout << "Last configuration: " << config << endl;
    cout << "Best configuration: " << bestConfig << endl;
    stringstream decoded;
    decode(bestConfig, text, decoded);
    cout << "Best decoded: " << decoded.str() << endl;
}

void crack(const std::string &text) {
//    map<string, int> digramCount;
//
//    for (int i = 0; i+1 < text.length(); i+=2) {
//        stringstream digram;
//        char c1 = text.at(i);
//        char c2 = text.at(i+1);
//        if (c1 < c2) {
//            digram << c1 << c2;
//        } else {
//            digram << c2 << c1;
//        }
//        cout << digram.str() << endl;
//        if(digramCount.find(digram.str()) == digramCount.end()) {
//            digramCount.insert({digram.str(), 1});
//        } else {
//            digramCount[digram.str()] += 1;
//        }
//    }
//    return;
    srand(time(NULL));
    std::string config = "abcdefghiklmnopqrstuvwxyz";
    stringstream output;
    decode(config, text, output);
    double score = getFrequencyScore(output.str());
    int cycles = 0;
    string bestShot = config;
    do {
        long counter = 0;
        double intermediateScore = 10000;
        std::string config = "abcdefghiklmnopqrstuvwxyz";
        do {
            int index1 = rand() % 25;
            int index2 = rand() % 25;
            if (index1 == index2) {
                continue;
            }
            char c1 = config.at(index1);
            char c2 = config.at(index2);
            config[index1] = c2;
            config[index2] = c1;

            stringstream verify;
            decode(config, text, verify);
            double updatedScore = getFrequencyScore(verify.str());

            if (updatedScore < intermediateScore) {
                intermediateScore = updatedScore;
            } else {
                config[index1] = c1;
                config[index2] = c2;
            }

        } while (++counter < 1000);
        if (intermediateScore < score) {
            score = intermediateScore;
            bestShot = config;
        }
    } while(++cycles < 200);
    cout << bestShot << endl;
    stringstream result;
    decode(bestShot, text,result);
    cout << "Decrypted: " << result.str() << endl;
}