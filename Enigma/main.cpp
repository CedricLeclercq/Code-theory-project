//
// Created by Cédric Leclercq on 30/10/2022.
//
#include "Enigma.h"
#include <string>
#include <vector>


int main() {
    // Defining all the variables from the assignment
    std::string rotor0 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";        /// Rotor 0 string
    std::string rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";        /// Rotor 1 string
    std::string rotor2 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";        /// Rotor 2 string
    std::string rotor3 = "THEQUICKBROWNFXJMPSVLAZYDG";        /// Rotor 3 string
    std::string rotor4 = "XANTIPESOKRWUDVBCFGHJLMQYZ";        /// Rotor 4 string
    std::string reflector = "AJDKSIRUXBLHWTMCQGZNPYFVOE";     /// Reflector string
    std::string crib = "DEOPGAVEVOORENIGMA";                  /// Crib string
    std::vector<std::string> rotors{rotor0, rotor1, rotor2, rotor3, rotor4};

    // Creating enigma object
    auto * enigma = new Enigma(rotors, reflector, crib);

    delete enigma;
    return 0;
}
