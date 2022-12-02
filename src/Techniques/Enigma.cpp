//
// Created by Cédric Leclercq on 30/11/2022.
//

#include "Enigma.h"
#include <string>

Enigma::Enigma(std::vector<std::string> p0, std::vector<std::string> p1, std::vector<std::string> p2,
               std::vector<std::string> p3, std::vector<std::string> p4, std::vector<std::string> sigma,
               std::vector<std::string> tau, std::vector<std::string> pi, std::vector<int> rotor_setting,
               std::vector<char> cur_pos) {
    this->p0_perm = std::move(p0);
    this->p1_perm = std::move(p1);
    this->p2_perm = std::move(p2);
    this->p3_perm = std::move(p3);
    this->p4_perm = std::move(p4);
    this->sigma_perm = std::move(sigma);
    this->tau_perm = std::move(tau);
    this->pi_perm = std::move(pi);
    this->rotor_choice = std::move(rotor_setting);
    this->cur_position = std::move(cur_pos);
}

char Enigma::encryptLetter(const char &ch) {

    return 0;
}




