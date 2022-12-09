//
// Created by Cédric Leclercq on 06/12/2022.
//

#include "AdvancedTuringBombe.h"
#include "Enigma.h"
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
        int countX = 0; // Every Row should have one 1
        int countY = 0; // Every Col should have one 1
        for (auto node: nodesX) {
            countX += node->correct;
        } if (countX != 1) return false;
        for (auto node: nodesY) {
            countY += node->correct;
        } if (countY != 1) return false;
        // Now checking the transitions
        for (auto vertex_pair: this->gammaGraph->transitions) {
            if (vertex_pair.first->correct != vertex_pair.second->correct)
                return false;
        }
    }
    return true;
}

void AdvancedTuringBombe::setup_cracking() {
    // 0. Setup gammaGraph nodes - begin
    std::string alphabet = Utilities::getAlphabet();
    this->gammaGraph = new GammaGraph();
    for (auto ch: alphabet) {
        for (auto ch2: alphabet) {
            auto * new_node = new GammaNode(ch, ch2, false);
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
    for (const auto& setting: permutations) {
        this->current_setting = setting;
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
    //std::cout << this->current_k[0] << this->current_k[1] << this->current_k[2] << std::endl;
    // Z Z Z
    if (this->current_k[0] == 'Z' && this->current_k[1] == 'Z' && this->current_k[2] == 'Z') {
        // We have done a full rotation without any luck, cracking has failed :(
        throw std::exception();
    }

    // x x Z
    if (this->current_k[2] == 'Z' && this->current_k[1] != 'Z') {

        this->current_k[1] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[1]);
        this->current_k[2] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[2]);
        return;
    }

    // x Z Z
    if (this->current_k[2] == 'Z' && this->current_k[1] == 'Z' && this->current_k[0] != 'Z') {
        this->current_k[2] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[2]);
        this->current_k[1] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[1]);
        this->current_k[0] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[0]);
        return;
    }

    // Always turn the fastest rotor
    this->current_k[2] = Utilities::followPermutation({Utilities::getAlphabet()}, this->current_k[2]);
}

void AdvancedTuringBombe::setup_gamma_for_cur_k() {
    this->gammaGraph->transitions.clear();
    // Setting up: (L_1, L_2) - (L_2, L_1)
    for (auto elemA: this->gammaGraph->nodes) {
        for (auto elemB: this->gammaGraph->nodes) {
            std::string full_a; full_a.push_back(elemA->letterA); full_a.push_back(elemA->letterB);
            std::string full_b; full_b.push_back(elemB->letterB); full_b.push_back(elemB->letterA);
            if (elemA != elemB && (full_a == full_b)) {
                std::pair<GammaNode*, GammaNode*> searchA{elemA, elemB}; // TODO: How to assign this? true or false
                std::pair<GammaNode*, GammaNode*> searchB{elemB, elemA};
                bool inside = (std::find(this->gammaGraph->transitions.begin(), this->gammaGraph->transitions.end(),
                                        searchA) != this->gammaGraph->transitions.end());
                inside = inside && (std::find(this->gammaGraph->transitions.begin(), this->gammaGraph->transitions.end(),
                                             searchB) != this->gammaGraph->transitions.end());
                if (!inside)
                    this->gammaGraph->transitions.emplace_back(elemA, elemB);
            }
        }
    }
    // Setting up: (L_1, L_3) - (L_2, e_(k+l)(L_3))
    for (auto transition: this->cribGraph->transitions) {
        char L_1 = std::get<0>(transition)->letter;
        char L_2 = std::get<1>(transition)->letter;
        std::vector<GammaNode*> nodesInRow = this->gammaGraph->getNodesWithALetter(L_1);
        std::vector<GammaNode*> nodesInRow2 = this->gammaGraph->getNodesWithALetter(L_2);
        for (auto L_3: nodesInRow) {
            char L_3_letter = L_3->letterB; // Letter to use for sigma calculation on row L_2
            Enigma enigma(this->p0_perm,this->p1_perm, this->p2_perm, this->p3_perm, this->p4_perm,
                          {}, // TODO: Plug board, what to enter here???
                          this->tau_perm,
                          {},
                          this->current_setting,
                          this->current_k
                          );
            char epsilonL_3 = enigma.encryptLetter(L_3_letter);
            for (auto item: nodesInRow2) {
                if (item->letterB == epsilonL_3) {
                    std::pair<GammaNode*, GammaNode*> searchA{L_3, item}; // TODO: how to assign this? true or false
                    std::pair<GammaNode*, GammaNode*> searchB{item, L_3};
                    bool inside = (std::find(this->gammaGraph->transitions.begin(), this->gammaGraph->transitions.end(),
                                             searchA) != this->gammaGraph->transitions.end());
                    inside = inside && (std::find(this->gammaGraph->transitions.begin(), this->gammaGraph->transitions.end(),
                                                  searchB) != this->gammaGraph->transitions.end());

                    if (!inside)
                        this->gammaGraph->transitions.emplace_back(L_3, item);
                }
            }
        }
    }
}


