#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include "../../Utilities/Utilities.h"

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
    std::vector<T> flatten(std::vector<std::vector<T>> const &vec){
        std::vector<T> flattened;
        for (auto const &v: vec) {
            flattened.insert(flattened.end(), v.begin(), v.end());
        }
    return flattened;
    }

}

string DecryptSingleColumnTranspositionAlphabatKey(const string &key, const string &Ciphertext) {
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

    // make list of matrix
    vector<char> CiphertextVector = flatten(CiphertextMatrix);

    // make string of matrix
    string result(CiphertextVector.begin(), CiphertextVector.end());
    return result;
}

string DecryptSingleColumnTranspositionIntKey(const string &key, const string &Ciphertext) {

    // make the empty matrix
    vector<vector<char>> CiphertextMatrix = makeEmptyMatrix(key, Ciphertext);

    // fill the matrix
    string text = Ciphertext;
    for (const char &i : key) {
        int index = i - '0';
        for (int j = 0; j < CiphertextMatrix.size(); j++) {
            if (CiphertextMatrix[j].size() > index && text.size() > 0){
                CiphertextMatrix[j][index] = (char) tolower(text[0]);
                text.erase(text.begin());
            }
        }
    }

    // make list of matrix
    vector<char> CiphertextVector = flatten(CiphertextMatrix);

    // make string of matrix
    string result(CiphertextVector.begin(), CiphertextVector.end());
    return result;
}


struct SequenceValue {
    vector<int> indexes;
    vector<int> spacing;
};

map<string, SequenceValue> FindRepeatedSequences(const string &Ciphertext){
    map<string, SequenceValue> RepeatedSequences;
    for (int i = 0; i < Ciphertext.size()-2; i++) {
        string triplet = Ciphertext.substr(i,3);
        // if triplet not registered yet add it to the RepeatedSequences
        if (RepeatedSequences.count(triplet) == 0){
            SequenceValue value;
            value.indexes.push_back(i);
            RepeatedSequences.insert({triplet, value});
        }
        else{
            // If we encounter the index again we will add the index
            SequenceValue *p = &RepeatedSequences[triplet];
            int last_index = p->indexes.back();
            p->indexes.push_back(i);
            int current_index = i;
            // we are going to calculate the distance from the current index and the previous index
            p->spacing.push_back(current_index-last_index);
        }
        if (i < Ciphertext.size() -3){
            string Quadruplets = Ciphertext.substr(i,4);
            if (RepeatedSequences.count(Quadruplets) == 0){
                SequenceValue value;
                value.indexes.push_back(i);
                RepeatedSequences.insert({Quadruplets, value});
            }
            else{
                // If we encounter the index again we will add the index
                SequenceValue *p = &RepeatedSequences[Quadruplets];
                int last_index = p->indexes.back();
                p->indexes.push_back(i);
                int current_index = i;
                // we are going to calculate the distance from the current index and the previous index
                p->spacing.push_back(current_index-last_index);
            }
        }
    }
    return RepeatedSequences;
}

vector<int> findDivisors(int n, int min_key_length, int max_key_length) {
    assert(n > 0);
    vector<int> devisors;
    // we assume that the key is not greater than 20
    for (int i = min_key_length; i <= max_key_length; i++) {
        if (n % i == 0) {
            devisors.push_back(i);
        }
    }
    return devisors;
}

pair<bool, vector<int>> IsPossibleVinegere(const map<string, SequenceValue>& repeated_sequences, const int& min_key_length ,const int& max_key_length ){
    assert(max_key_length > 1);
    map<int, int> devisors;
    for (auto const& sequence : repeated_sequences){
        for (const int & space : sequence.second.spacing){
            vector<int> devisorsList = findDivisors(space, min_key_length, max_key_length);
            for(const int &i : devisorsList){
                if (devisors.count(i) == 0){
                    devisors.insert({i, 1});
                }
                else{
                    devisors[i] += 1;
                }
            }
        }
    }
    /*
    for (auto const& devisor : devisors){
        cout << devisor.first << ": " << devisor.second << ", ";
    }
    cout << endl;
     */

    bool isPossibleVinegere = false;
    // Create a boxplot to find outliers
    vector<int> devisors_values;
    devisors_values.reserve(devisors.size());
    for (auto const& devisor : devisors){
        devisors_values.push_back(devisor.second);
    }
    sort(devisors_values.begin(), devisors_values.end());
    int mid = devisors_values.size() / 2 +1;
    int lower_Quartile = devisors_values[mid/2];
    int upper_quartile = devisors_values[(devisors_values.size() + mid)/2 + 1];
    int IQR = upper_quartile - lower_Quartile;
    int upper_boundary = (1.5 * IQR) + upper_quartile;
    vector<int> key_lengths;
    for (auto const& devisor : devisors) {
        if (devisor.second > upper_boundary) {
            key_lengths.push_back(devisor.first);
            cout << "-----------------:" << devisor.first << ": " << devisor.second << endl;
            for (auto const& devisor_ : devisors){
                if (devisor_.first % devisor.first == 0){
                    cout << devisor_.first << ": " << devisor_.second << ", ";
                }
            }
            cout << endl;
            cout << endl;
            isPossibleVinegere = true;
        }
    }


    return make_pair(isPossibleVinegere, key_lengths);
}

map<string, string> GetPossibleCipherByKeyLength(const int &keyLengthColumnTranspose, const string &Ciphertext, const string &inputfile, const pair<int,int> & keyLengthVinegere){
    assert(keyLengthColumnTranspose > 1);
    assert(keyLengthVinegere.first > 1);
    assert(keyLengthVinegere.second > 1);
    assert(keyLengthVinegere.first < keyLengthVinegere.second);
    assert(inputfile != "");
    map<string, string> results;
    Utilities utilities;
    string permutation_key = "";
    for (int i = 0; i < keyLengthColumnTranspose; i++) {
        permutation_key += to_string(i);
    }
    vector<string> all_permutations = utilities.simplePermutations(permutation_key);
    for (const string & key : all_permutations) {
        // do the column transposition with a possible (column transposition key) key
        string possible_ciphertext = DecryptSingleColumnTranspositionIntKey(key, Ciphertext);
        // find the repeated sequence in the possible ciphertexts
        map<string, SequenceValue> repeated_sequences = FindRepeatedSequences(possible_ciphertext);
        // test whether the outcome can be a possible vinegere cipher
        auto possible_vinegere = IsPossibleVinegere(repeated_sequences, keyLengthVinegere.first, keyLengthVinegere.second);
        // if that is the case we write it to a file
        if( possible_vinegere.first ){
            string possible_key_sizes = " ";
            for (const int &i: possible_vinegere.second ){
                possible_key_sizes += to_string(i) +" ";
            }
            utilities.WriteContents(inputfile, key+"(possible vinegere keys:"+ possible_key_sizes +"): "+possible_ciphertext+"\n");
            results[key] = possible_ciphertext;
        }
    }
    return results;
}