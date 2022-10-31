#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// I put the helper functions in an unnamed namespace, so it is not accessible to the user
namespace {

    vector<char> alphabaticallySort(vector<char> &a) {
        sort(a.begin(), a.end(), [](const char &a, const char &b) { return a < b; });
        return a;
    }

    vector<pair<char, int>> keyOrderSort(vector<pair<char, int>> KeyAndVal, const string &key){
        vector<pair<char, int>> result;
        for (auto const & chars : key) {
            int index = distance(KeyAndVal.begin(), find_if( KeyAndVal.begin(), KeyAndVal.end(), [&chars](const pair<char, int>& element) { return element.first == chars; }));
            result.push_back(KeyAndVal[index]);
            std::remove(KeyAndVal.begin(), KeyAndVal.end(), KeyAndVal[index]);
        }
        return result;
    }

    vector<vector<char>> makeEmptyMatrix(const string &key, const string &Ciphertext){
        vector<vector<char>> result;
        int ciphertextSize = Ciphertext.size();
        int rowCount = ceil( Ciphertext.size() / key.size());
        for (int i = 0; i <= rowCount; i++) {
            vector<char> row;
            int elementsPerRow;
            if (ciphertextSize >= key.size()){
                elementsPerRow = key.size();
            }
            else{
                elementsPerRow = ciphertextSize % key.size() ;
            }
            for (int j = 0; j < elementsPerRow; j++) {
                row.push_back('_');
            }
            result.push_back(row);
            ciphertextSize -= key.size();
        }
        return result;
    }

    template<typename T>
    std::vector<T> flatten(std::vector<std::vector<T>> const &vec)
{
    std::vector<T> flattened;
    for (auto const &v: vec) {
    flattened.insert(flattened.end(), v.begin(), v.end());
}
return flattened;
}

}

string DecryptEnkeleKolomTranspositie(const string &key, const string &Ciphertext) {
    // put the key in a vector and sort the key alphabetically
    std::vector<char> keyVector(key.begin(), key.end());
    alphabaticallySort(keyVector);

    // Link the correct value to the character
    int counter = 0;
    vector<pair<char, int>> KeyAndVal;
    for (auto const & chars : keyVector) {
        KeyAndVal.push_back(make_pair(chars, counter));
        counter++;
    }

    // put the letters back in the order of the key
    vector<pair<char, int>> SortedKeyAndVal = keyOrderSort(KeyAndVal, key);

    // make the empty matrix
    vector<vector<char>> CiphertextMatrix = makeEmptyMatrix(key, Ciphertext);

    // fill the matrix
    string text = Ciphertext;
    for (int i = 0; i < key.size(); i++) {
        int index = distance(SortedKeyAndVal.begin(), find_if( SortedKeyAndVal.begin(), SortedKeyAndVal.end(), [&i](const pair<char, int>& element) { return element.second == i; }));
        for (int j = 0; j < CiphertextMatrix.size(); j++) {
            if (CiphertextMatrix[j].size() > index && text.size() > 0){
                CiphertextMatrix[j][index] = (char) tolower(text[0]);
                text.erase(text.begin());
            }
        }
    }

    vector<char> CiphertextVector = flatten(CiphertextMatrix);

    string result(CiphertextVector.begin(), CiphertextVector.end());
    return result;
}
