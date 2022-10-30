#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/*
 * 1) Read inputs and dictionary
 * 2) Make permutations
 * 3) Generate decryption
 * 4) Check for words in dictionary
 */

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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
