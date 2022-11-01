//
// Created by Cédric Leclercq on 31/10/2022.
//

#ifndef CODE_THEORY_UTILITIES_H
#define CODE_THEORY_UTILITIES_H
#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <map>

using namespace std;

class Utilities {
public:
    Utilities();

    tuple< map< string, string >, string> ReadContents(const string &inputfile);
private:

};


#endif //CODE_THEORY_UTILITIES_H