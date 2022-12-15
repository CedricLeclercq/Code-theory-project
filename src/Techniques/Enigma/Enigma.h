//
// Created by Cédric Leclercq on 30/11/2022.
//

#ifndef CODE_THEORY_ENIGMA_H
#define CODE_THEORY_ENIGMA_H

#include <vector>
#include <string>

class Enigma {
    std::vector<std::string> p0_perm; // Rotor 0 - permutation
    std::vector<std::string> p1_perm; // Rotor 1 - permutation
    std::vector<std::string> p2_perm; // Rotor 2 - permutation
    std::vector<std::string> p3_perm; // Rotor 3 - permutation
    std::vector<std::string> p4_perm; // Rotor 4 - permutation
    std::vector<std::string> sigma_perm; // Plugboard - permutation
    std::vector<std::string> tau_perm; // Reflector - permutation
    std::vector<std::string> pi_perm; // Cyclo-metric - permutation
    std::vector<int> rotor_choice; // Slow - Mid - Fast
    std::vector<char> cur_position; // Slow - Mid - Fast
    int rotations = 0; // Rotation amount

public:
    Enigma(std::vector<std::string> p0,
           std::vector<std::string> p1,
           std::vector<std::string> p2,
           std::vector<std::string> p3,
           std::vector<std::string> p4,
           std::vector<std::string> sigma,
           std::vector<std::string> tau,
           std::vector<std::string> pi,
           std::vector<int> rotor,
           std::vector<char> cur_pos);

    char encryptLetter(const char& ch);

    void rotateRotors();
};


#endif //CODE_THEORY_ENIGMA_H
