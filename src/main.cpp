//
// Created by Cédric Leclercq on 30/10/2022.
//

#include "System/System.h"
#include <exception>
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        if (argv[1] == nullptr) {
            std::cerr << "WARNING: No parameter was provided." << std::endl;
            std::cout << "Tip: Use parameter: <Enigma>, <Playfair>, <VigenerePlus> or <All>" << std::endl;
            return 1;
        }

        if (static_cast<std::string>(argv[1]) == "Enigma") System::runEnigma();
        else if (static_cast<std::string>(argv[1]) == "Playfair") System::runPlayfair();
        else if (static_cast<std::string>(argv[1]) == "adfgvx") System::ADFGVX();
        else if (static_cast<std::string>(argv[1]) == "VigenerePlus"){
            if(argv[2]){
                System::runVigenerePlus(argv[2]);
            }
            else{
                System::runVigenerePlus();
            }
        }
        else if (static_cast<std::string>(argv[1]) == "All") {
            System::runEnigma();
            System::runPlayfair();
            System::runVigenerePlus();
        }
    } catch(std::exception & ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}





void runEnigma() {

}
