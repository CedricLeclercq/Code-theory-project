#include "adfgvx.h"

const std::string MAGIC = "adfgvx";

std::string adfgvx::encode(std::string message, std::string secret_alphabet1, std::string keyword) {
    // remove duplicate character from keyword -> key
    std::string key;
    for (const char &c: keyword) {
        if (key.find(c) == std::string::npos) {
            key += c;
        }
    }

    // make sort index
    int n = key.length();
    std::vector<int> k(n);
    std::iota(k.begin(), k.end(), 0);
    std::sort(k.begin(), k.end(), [&key](int i, int j) { return key[i] < key[j]; });

    // encode
    std::string s;
    for (const char &c: message) {
        if (std::isalpha(c) || std::isdigit(c)) {
            int row = secret_alphabet1.find(c) / 6;
            int col = secret_alphabet1.find(c) % 6;
            s += MAGIC[row];
            s += MAGIC[col];
        }
    }

    // reorder
    std::string result;
    for (int i: k) {
        for (int j = i; j < s.size(); j += n) {
            result += s[j];
        }
    }

    return result;
}


// decode function
std::string adfgvx::decode(std::string message, std::string secret_alphabet1, std::string keyword) {
    // remove duplicate character from keyword -> key
    std::vector<char> key;
    for (char c: keyword) {
        if (std::find(key.begin(), key.end(), c) == key.end()) {
            key.push_back(c);
        }
    }

    // make sort index
    int n = key.size();
    std::vector<int> k(n);
    std::iota(k.begin(), k.end(), 0);
    std::sort(k.begin(), k.end(), [&key](int a, int b) { return key[a] < key[b]; });

    // make reorder index
    int m = message.length();
    std::vector<int> x;
    for (int i: k) {
        for (int j = i; j < m; j += n) {
            x.push_back(j);
        }
    }

    // reorder
    std::vector<char> y(message.size());
    for (int i = 0; i < message.size(); ++i)
    {
        y[x[i]] = message[i];
    }

    // decode
    std::vector<char> s;
    for (int i = 0; i < y.size(); i += 2)
    {
        const char row = y[i];
        const char col = y[i + 1];
        s.push_back(secret_alphabet1[6 * MAGIC.find(row) + MAGIC.find(col)]);
    }
    return std::string(s.begin(), s.end());
}