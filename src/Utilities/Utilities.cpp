//
// Created by Cédric Leclercq on 31/10/2022.
//

#include <algorithm>
#include "Utilities.h"
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

tuple< map<string, string>, string > Utilities::ReadContents(const string &inputfile){
    map<string, string> ExtraInfo;
    string Ciphertext;

    std::ifstream myfile;
    myfile.open(inputfile);
    std::string myline;
    if ( myfile.is_open() ) {
        while ( myfile ) {
            std::getline (myfile, myline);
            // Find first occurrence of "geeks"
            size_t pos = myline.find(":");
            if (pos != string::npos){
                string key = myline.substr(0, pos);
                string value = myline.substr(pos+1);
                value.erase(std::remove_if(value.begin(), value.end(), isWhitespace), value.end());
                ExtraInfo[key] = value;
            }
            else if(myline.size() > 0){
                myline.erase(std::remove_if(myline.begin(), myline.end(), isWhitespace), myline.end());
                Ciphertext = myline;
            }
        }
    }
    else {
        std::cout << "Couldn't open file\n";
    }

    // Close the file
    myfile.close();
    return tuple<map<string, string>, string>{ExtraInfo, Ciphertext};
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


