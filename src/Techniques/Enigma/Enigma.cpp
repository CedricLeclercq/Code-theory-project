//
// Created by Cédric Leclercq on 30/10/2022.
//

#include "Enigma.h"

#include <utility>
using namespace std;

Enigma::Enigma(std::vector<std::string> newRotors, std::string newReflector, std::string newCrib) {
    this->setup_enigma(std::move(newRotors), std::move(newReflector), std::move(newCrib));
}

void Enigma::setup_enigma(vector<string> newRotors, string newReflector, string newCrib) {
    assert(newRotors.size() == 5);  // Max five rotors are allowed
    this->rotor0 = std::move(newRotors[0]);
    this->rotor1 = std::move(newRotors[1]);
    this->rotor2 = std::move(newRotors[2]);
    this->rotor3 = std::move(newRotors[3]);
    this->rotor4 = std::move(newRotors[4]);
    this->reflector = std::move(newReflector);
    this->crib = std::move(newCrib);
}

std::string Enigma::decrypt(const string & cypher) {
    return {};
}

std::string Enigma::encrypt(const string &cypher) {
    return {};
}
