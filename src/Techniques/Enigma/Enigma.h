//
// Created by Cédric Leclercq on 30/10/2022.
//

#ifndef CODE_THEORY_PROJECT_ENIGMA_H
#define CODE_THEORY_PROJECT_ENIGMA_H

#include <string>
#include <vector>

class Enigma {
private:
    // Variables
    std::string rotor0, rotor1, rotor2, rotor3, rotor4;    /// All rotors
    std::string reflector, crib;                           /// Reflector and crib
    int rotor_turn_count = 0;                              /// Rotor turn count (indicates # rotor turns happened)


    // Functions
    /**
     * @brief Function that turns the rotors automatically by using modulo
     */
    void turn_rotor() {}
public:
    /**
     * @brief Default constructor
     */
    Enigma()=default;

    /**
     * @brief Constructor that setups enigma directly
     * @param newRotors         New rotors for the enigma
     * @param newReflector      New reflector for the enigma
     * @param newCrib           New crib for the enigma
     */
    Enigma(std::vector<std::string> newRotors, std::string newReflector, std::string newCrib);

    /**
     * @brief Default destructor
     */
     ~Enigma()=default;

    /**
     * @brief Setup enigma with new rotors, reflector and crib
     * @param newRotors     New rotors for the enigma
     * @param newReflector  New reflector for the enigma
     * @param newCrib       New crib for the enigma
     * @pre std::vector<std::string> length == 5    (We have 5 rotors, they all need to be set)
     */
    void setup_enigma(std::vector<std::string> newRotors, std::string newReflector, std::string newCrib);

    std::string decrypt(const std::string & cypher);

    std::string encrypt(const std::string & cypher);

};


#endif //CODE_THEORY_PROJECT_ENIGMA_H
