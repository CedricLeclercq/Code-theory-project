#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

/*
 * 1) Read inputs and dictionary
 * 2) Make permutations
 * 3) Generate decryption
 * 4) Check for words in dictionary
 */

int evaluate() {
    // for every match found, add the substring length^2
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

    for (auto & i : v)
        cout << i << endl;
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
    loadDictionary("dictionaries/dutch.txt", dutch);
    loadDictionary("dictionaries/english.txt", english);
    loadDictionary("dictionaries/french.txt", french);
    loadDictionary("dictionaries/german.txt", german);
    loadDictionary("dictionaries/spanish.txt", spanish);
    return 0;
}
