//
// Created by Cédric Leclercq on 30/10/2022.
//

#include "System/System.h"
#include<exception>
#include <iostream>

int main() {
    try {
        System::runEnigma();
        System::runPlayfair();
        System::runVigenerePlus();
    } catch(std::exception & ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}





void runEnigma() {

}
