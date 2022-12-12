//
// Created by Cédric Leclercq on 30/10/2022.
//

#ifndef CODE_THEORY_PROJECT_ENIGMA_H
#define CODE_THEORY_PROJECT_ENIGMA_H

#include <string>
#include <vector>
#include "EnigmaNode.h"

class Enigma {
private:
    // Variables
    std::string rotor0, rotor1, rotor2, rotor3, rotor4;    /// All rotors
    std::string reflector, crib;                           /// Reflector and crib


    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";   /// Just the alphabet
    std::string coded_message{};

    std::vector<EnigmaNode*> cribGraph{};

    // Functions
    /**
     * @brief Setup enigma with new rotors, reflector and crib
     * @param newRotors     New rotors for the enigma
     * @param newReflector  New reflector for the enigma
     * @param newCrib       New crib for the enigma
     * @pre std::vector<std::string> length == 5    (We have 5 rotors, they all need to be set)
     */
    void setup_enigma(std::vector<std::string> newRotors, std::string newReflector, std::string newCrib);

    void setup_cribGraph();

    EnigmaNode * findInCribGraph(char x);

public:
    /**
     * @brief Constructor that setups enigma directly
     * @param newRotors         New rotors for the enigma
     * @param newReflector      New reflector for the enigma
     * @param newCrib           New crib for the enigma
     */
    Enigma(std::vector<std::string> newRotors, std::string newReflector, std::string newCrib, std::string code);

    /**
     * @brief Default destructor
     */
     ~Enigma()=default;


};


#endif //CODE_THEORY_PROJECT_ENIGMA_H
