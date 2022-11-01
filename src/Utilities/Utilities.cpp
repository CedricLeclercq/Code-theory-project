//
// Created by Cédric Leclercq on 31/10/2022.
//

#include <algorithm>
#include "Utilities.h"

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


