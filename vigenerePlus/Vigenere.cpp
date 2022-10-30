#include "Vigenere.h"

Vigenere::Vigenere(const string &key) : key(key) {

    // temporarily flip the alphabet dictionary, so we can make the square easier
    // {"A" : 0} -> {0 : A} ...
    map<int, char> flipped_aphabet;
    for (auto & i : this->alphabet) {
        flipped_aphabet[i.second] = i.first;
    }

    // making the vigenere square
    for (int i = 0; i < 26; i++) {
        vector<char> row;
        for (int j = i; j < i+26; j++) {
            row.push_back(flipped_aphabet[j % 26]);

        }
        this->vigenere_square.push_back(row);
    }

}

string Vigenere::encrypt(const string &Plaintext) {
    string result;
    for (int i = 0; i < Plaintext.size(); i++)  {
        // find the index of the correct row
        int key_row  = this->alphabet[(char) toupper(this->key[i % this->key.size()])];
        // find the index of the correct column
        int plaintext_column = this->alphabet[(char) toupper(Plaintext[i])];
        // look up the char in the vigenere square and add the obtained letter to the result
        result.push_back((char) tolower(this->vigenere_square[key_row][plaintext_column]));
    }
    return result;
}

string Vigenere::decrypt(const string &Ciphertext) {

    // temporarily flip the alphabet dictionary, so we can make the square easier
    // {"A" : 0} -> {0 : A} ...
    map<int, char> flipped_aphabet;
    for (auto & i : this->alphabet) {
        flipped_aphabet[i.second] = i.first;
    }

    string result;
    for (int i = 0; i < Ciphertext.size(); i++)  {
        // find the index of the correct row
        int key_row = this->alphabet[(char) toupper(this->key[i % this->key.size()])];
        // find the row
        vector<char> row = this->vigenere_square[key_row];
        // find the index of the letter of the Ciphertext text in the row
        auto it = find(row.begin(), row.end(),(char) toupper(Ciphertext[i]));
        if (it != row.end())
        {
            // look up the index in the alphabet and add the obtained letter to the result
            int plaintext_column = (int) (it - row.begin());
            result.push_back((char) tolower(flipped_aphabet[plaintext_column]));
        }
        else{
            cout << "Something went wrong. ";
            cout << "Check for strange character in the Ciphertext" << endl;
            break;
        }
    }
    return result;
}

