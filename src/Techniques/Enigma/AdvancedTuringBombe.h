//
// Created by Cédric Leclercq on 06/12/2022.
//

#ifndef CODE_THEORY_ADVANCEDTURINGBOMBE_H
#define CODE_THEORY_ADVANCEDTURINGBOMBE_H

#include<vector>
#include <string>
#include "GammaGraph.h"
#include "CribGraph.h"


class AdvancedTuringBombe {
private:
    /// Current k of our Gamma_k gammaGraph
    std::vector<char> current_k = {'A','A', 'A'};
    /// Current setting
    std::vector<int> current_setting = {};
    /// Current gamma k gammaGraph
    GammaGraph * gammaGraph{};
    /// Crib graph
    CribGraph * cribGraph{};
    /// Rotor 0 - permutation
    std::vector<std::string> p0_perm;
    /// Rotor 1 - permutation
    std::vector<std::string> p1_perm;
    /// Rotor 2 - permutation
    std::vector<std::string> p2_perm;
    /// Rotor 3 - permutation
    std::vector<std::string> p3_perm;
    /// Rotor 4 - permutation
    std::vector<std::string> p4_perm;
    /// Reflector - permutation
    std::vector<std::string> tau_perm;
    /// Crib
    std::string crib;
    /// Code
    std::string code;
    /**
     * Checks if our gammaGraph applies to the two given rules.
     * @return      True if code is cracked
     */
    bool check_graph();
    /**
     * Increases k of the turing bombe
     */
    void increase_k();
    /**
     * Increases k and returns the vector
     */
     static std::vector<char> increase_k(std::vector<char> cur_k);
    /**
     * Sets up the the gamma_k gammaGraph for the current k
     */
    void setup_gamma_for_cur_k();

    void setup_cracking();

public:

    AdvancedTuringBombe(std::vector<std::string> p0, std::vector<std::string> p1,
                        std::vector<std::string> p2, std::vector<std::string> p3,
                        std::vector<std::string> p4, std::vector<std::string> tau,
                        std::string crib, std::string code);

    std::string crack_enigma();
};


#endif //CODE_THEORY_ADVANCEDTURINGBOMBE_H
