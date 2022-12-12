//
// Created by Cédric Leclercq on 31/10/2022.
//

#include <algorithm>
#include "Utilities.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

Utilities::Utilities() {}

bool isWhitespace(unsigned char c){
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'){
        return true;
    }
    else{
        return false;
    }
}

void Utilities::WriteContents(const string &inputfile, const string &content){
    std::ofstream myfile;
    myfile.open(inputfile, fstream::app);
    if (myfile.is_open())
    {
        myfile << content;
        myfile.close();
    }
    else {
        std::cout << "Couldn't open file\n";
    }
}

void Utilities::ClearContents(const string &inputfile){
    std::ofstream ofs;
    ofs.open(inputfile);
    ofs.close();
}

std::vector<std::string> Utilities::convertToPermutation(std::string dom,  std::string ran) {
    // Assert strings are same length and not empty
    assert(!dom.empty() && dom.length() == ran.length());
    // Checking is each of them have the same chars in them
    std::string temp1 = dom, temp2 = ran;
    std::sort(temp1.begin(), temp1.end()); // Sorted dom
    std::sort(temp2.begin(), temp2.end()); // Sorted ran
    assert(temp1 == temp2); // Assert they contain the same things
    // Asserting domain has at max one char of each kind
    for (int i = 0; i < dom.length(); i++) {
        for (int j = 0; j < dom.length(); j++) {
            if (dom[i] == dom[j])
                assert(i == j); // Assert if two are the same => they are on the same index => Assertion failure if not
        }
    }
    // DONE WITH ASSERTIONS :))

    // Beginning function
    std::vector<std::string> all_perms{};
    std::string dom_remains = dom;

    unsigned long dom_iterator = 0;
    char new_dom_letter = dom[dom_iterator];
    char cur_handling = new_dom_letter;
    std::string cur_perm{};
    while(!dom_remains.empty()) {
        new_dom_letter = ran[dom_iterator];
        if (!cur_perm.empty() && cur_handling == new_dom_letter) {
            // If this permutation is done
            cur_perm += new_dom_letter;
            all_perms.push_back(cur_perm);
            dom_remains.erase(dom_iterator,1);
            ran.erase(ran.find(new_dom_letter),1);
            dom_iterator = 0;
            cur_perm = "";
            cur_handling = dom_remains[dom_iterator];

        } else if (cur_perm.empty() && new_dom_letter == dom_remains[dom_iterator]) {
            // If we just have a permutation of size 1: e.g.: a -> a
            all_perms.emplace_back(1, new_dom_letter);
            dom_remains.erase(dom_iterator,1);
            ran.erase(ran.find(new_dom_letter),1);
            dom_iterator = 0;
            cur_perm = "";
            cur_handling = dom_remains[dom_iterator];
        } else {
                cur_perm += new_dom_letter;
                dom_remains.erase(dom_iterator,1);
                ran.erase(ran.find(new_dom_letter),1);
                dom_iterator = dom_remains.find(new_dom_letter);
            }
        }

    return all_perms;
}

void Utilities::leftRotate(string &s, int d) {
    reverse(s.begin(), s.begin()+d);
    reverse(s.begin()+d, s.end());
    reverse(s.begin(), s.end());
}

void Utilities::rightRotate(string &s, int d) {
    leftRotate(s, s.length() - d);
}

char Utilities::followPermutation(const vector<std::string> &perm, const char &ch) {
    // Assert that we can find the char in one permutation and that we can find that permutation
    bool contains = false;
    std::string needed_perm{};
    for (const auto& ev_perm: perm) {
        if (ev_perm.find(ch) != std::string::npos) {
            contains = true;
            needed_perm = ev_perm;
        }
    }
    if (not contains or needed_perm.empty()) {
        return ch;
    }
    // assert(contains && !needed_perm.empty());

    // Find the next permutation
    unsigned long pos_in_str = needed_perm.find(ch);
    if (pos_in_str == needed_perm.size() - 1)
        return needed_perm[0];
    else return needed_perm[pos_in_str+1];
}

char Utilities::InverseFollowPermutation(const vector<std::string> &perm, const char& ch) {
    // Assert that we can find the char in one permutation and that we can find that permutation
    bool contains = false;
    std::string needed_perm{};
    for (const auto& ev_perm: perm) {
        if (ev_perm.find(ch) != std::string::npos) {
            contains = true;
            needed_perm = ev_perm;
        }
    }
    if (not contains or needed_perm.empty()) {
        return ch;
    }
    //assert(contains && !needed_perm.empty());

    // Find the previous permutation
    unsigned long pos_in_str = needed_perm.find(ch);
    if (pos_in_str == 0) {
        return needed_perm.back();
    }
    else return needed_perm[pos_in_str-1];
}

char Utilities::cyclometric_continuation(const std::string& dom, const char& ch, int k) {
    assert(k < static_cast<int>((2*dom.size() - 2)));
    unsigned long pos = dom.find(ch);
    assert(pos != std::string::npos);
    if (k >= 0 && pos + k >= dom.size()) {
        k -= static_cast<int>(dom.size() - pos);
        return dom[k];
    } else if (k < 0 && static_cast<int>(pos) - std::abs(k) < 0) {
        k += static_cast<int>(pos);
        return dom[dom.size() + k];
    } // 1 2 3 4 5 6

    return dom[pos + k];
}

void permute(string s, string temp, vector<string> & answer)
{
    if (s.length() == 0) {
        answer.push_back(temp);
        return;
    }
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        string left_substr = s.substr(0, i);
        string right_substr = s.substr(i + 1);
        string rest = left_substr + right_substr;
        permute(rest, temp + ch, answer);
    }
}

std::vector<std::string> Utilities::simplePermutations(const std::string& s) {
    vector<string> answer;
    string temp;
    permute(s, temp, answer);
    return answer;
}
std::vector<std::vector<int>> Utilities::createEnigmaRotorPermutations(std::vector<int> all_rotors) {
    std::vector<std::vector<int>> permutations{};
    while (std::next_permutation(all_rotors.begin(), all_rotors.end())) {
        std::vector<int> result = {all_rotors[0], all_rotors[1], all_rotors[2]};
        bool add = true;
        for (const auto& elem: permutations) {
            if (elem == result)
                add = false;
        }
        if (add)
            permutations.push_back(result);
    }
    return permutations;
}




