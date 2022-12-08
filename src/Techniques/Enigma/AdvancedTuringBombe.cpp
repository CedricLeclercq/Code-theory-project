//
// Created by Cédric Leclercq on 06/12/2022.
//

#include "AdvancedTuringBombe.h"
#include "../../Utilities/Utilities.h"

AdvancedTuringBombe::AdvancedTuringBombe(std::vector<std::string> p0, std::vector<std::string> p1,
                                         std::vector<std::string> p2, std::vector<std::string> p3,
                                         std::vector<std::string> p4, std::vector<std::string> tau,
                                         std::string crib, std::string code) {
    this->p0_perm = std::move(p0);
    this->p1_perm = std::move(p1);
    this->p2_perm = std::move(p2);
    this->p3_perm = std::move(p3);
    this->p4_perm = std::move(p4);
    this->tau_perm = std::move(tau);
    this->crib = std::move(crib);
    this->code = std::move(code);
}


bool AdvancedTuringBombe::check_graph() {
    std::string alphabet = Utilities::getAlphabet();
    for (auto ch: alphabet) {
        std::vector<GammaNode *> nodesX = this->gammaGraph->getNodesWithALetter(ch);
        std::vector<GammaNode *> nodesY = this->gammaGraph->getNodesWithBLetter(ch);
    }
}

void AdvancedTuringBombe::setup_cracking() {
    // 0. Setup gammaGraph nodes - begin
    std::string alphabet = Utilities::getAlphabet();
    this->gammaGraph = new GammaGraph();
    for (auto ch: alphabet) {
        for (auto ch2: alphabet) {
            auto * new_node = new GammaNode(ch, ch2);
            this->gammaGraph->nodes.push_back(new_node);
        }
    }
    // 0. Setup gammaGraph nodes - end
    // 1. Setup crib graph fully - begin
    std::string meaning = this->code;
    meaning.substr(0, this->crib.size());
    this->cribGraph = new CribGraph(this->crib, meaning); // todo assume the crib is in the beginning?
    // 1. Setup crib graph fully - end
}


std::string AdvancedTuringBombe::crack_enigma() {

    // 1. Setup cracking
    this->setup_cracking();
    // 2. Run the main loop with testing all the different settings - begin
    bool found = false;
    std::vector<std::vector<int>> permutations = Utilities::createEnigmaRotorPermutations({0,1,2,3,4});
    // MAIN LOOP
    // 2.2. Loop over all possible rotor settings (there are (6,5,4) = 6*5*4 = 60 possible ones)
    for (auto setting: permutations) {
        try {
            while (!found) {
                this->setup_gamma_for_cur_k();
                found = this->check_graph();
                this->increase_k();
            }
            // If found we have the correct K and the correct rotor stand and the correct plug board
            // Now create new enigma and fill in the old text and find the original text
            // todo What to do if found?
        } catch (std::exception& e) {
            continue;
        }
    }

    // END MAIN LOOP
    return {};
}

void AdvancedTuringBombe::increase_k() {

    if (this->current_k[0] == 'Z' && this->current_k[1] == 'Z' && this->current_k[2] == 'Z') {
        // We have done a full rotation without any luck, cracking has failed :(
        throw std::exception();
    }

    if (this->current_k[1] == 'Z') {
        // std::cout << this->current_k[0] << this->current_k[1] << this->current_k[2] << std::endl;
        this->current_k[0] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                             this->current_k[0]);
    }
    if (this->current_k[2] == 'Z') {
        this->current_k[1] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                             this->current_k[1]);
    }

    // Always turn the fastest rotor
    this->current_k[2] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                         this->current_k[2]);
}

void AdvancedTuringBombe::setup_gamma_for_cur_k() {
    // Setting up: (L_1, L_2) - (L_2, L_1)

    // Setting up: (L_1, L_3) - (L_2, e_(k+l)(L_3))
}


