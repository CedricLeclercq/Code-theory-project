#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "playfair.h"

using namespace std;

/*
 * 1) Read inputs and dictionary
 * 2) Make permutations
 * 3) Generate decryption
 * 4) Check for words in dictionary
 */

int evaluate() {
    // for every match found, add the substring length^2
    return 0;
}


void playfair() {
    // for every permutation:
    //      reverse engineer
    //          count hits
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

int main() {
    vector<string> dutch, english, french, german, spanish;
    loadDictionary("dictionaries_without_j/dutch.txt", dutch);
    loadDictionary("dictionaries_without_j/english.txt", english);
    loadDictionary("dictionaries_without_j/french.txt", french);
    loadDictionary("dictionaries_without_j/german.txt", german);
    loadDictionary("dictionaries_without_j/spanish.txt", spanish);
    string config = "palmerstonbcdfghikquvwxyz";
    cout << encrypt("dk dk", config);
    return 0;
}
