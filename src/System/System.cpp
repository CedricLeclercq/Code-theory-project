//
// Created by Cédric Leclercq on 31/10/2022.
//

#include "System.h"
#include "../Techniques/Enigma/Enigma.h"
#include "../Techniques/VigenerePlus/Vigenere.h"
#include "../Techniques/VigenerePlus/Transposition.cpp"
#include <vector>

void System::runVigenerePlus() {
    Vigenere Code = Vigenere("PYRAMID");
    std::cout << Code.encrypt("attackatsundown") << std::endl;
    std::cout << Code.decrypt("prkaosdiqlnpwzc") << std::endl;
    std::cout << DecryptEnkeleKolomTranspositie("OSYMANDIAS", "AHGARYDAHPLPCYNEOCRMOEASIMAR") << std::endl;
}

void System::runEnigma() {
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
}

void System::runPlayfair() {
    // todo ROBBE
}
