//
// Created by Cédric Leclercq on 06/12/2022.
//

#include "AdvancedTuringBombe.h"
#include "Enigma.h"
#include <thread>
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


bool AdvancedTuringBombe::check_permutation_graph() {
    std::string alphabet = Utilities::getAlphabet();
    for (auto ch: alphabet) {
        std::vector<GammaNode *> nodesX = this->gammaGraph->getNodesWithALetter(ch);
        std::vector<GammaNode *> nodesY = this->gammaGraph->getNodesWithBLetter(ch);
        int countX = 0; // Every Row should have one 1
        int countY = 0; // Every Col should have one 1
        for (auto node: nodesX) {
            countX += node->correct;
        } if (countX > 1) return false;
        for (auto node: nodesY) {
            countY += node->correct;
        } if (countY > 1) return false;
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
    // this->cribGraph = new CribGraph("KEINEZUSAETZEZUMVORBERIQT", "DAEDAQOZSIQMMKBILGMPWHAIV"); // todo assume the crib is in the beginning?
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
        this->current_k = {'A','A','A'};
//         this->current_k = {'F','E','J'};  // @Professor Symens - so you don't need to wait to finish running
//         this->current_setting = {1,3,2};
        try {
            while (!found) {
                this->setup_gamma_for_cur_k();
                found = this->check_permutation_graph();
                this->increase_k();
            }
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
    this->count += 1;
    if (this->current_k[0] == 'Z' && this->current_k[1] == 'Z' && this->current_k[2] == 'Z') {
        // We have done a full rotation without any luck, cracking has failed :(
        throw std::exception();
    }

    // x x Z
    if (this->current_k[2] == 'Z' && this->current_k[1] != 'Z') {
//        std::cout << "Testing ENIGMA rotors [";
//        std::cout << this->current_setting[0] << this->current_setting[1] << this->current_setting[2];
//        std::cout << "] on iteration [" <<  26 << " * " << to_string((this->count)/26) << "] with rotation: [";
//        std::cout << this->current_k[0] << this->current_k[1] << this->current_k[2];
//        std::cout << "] \t \t | Time used: " << chrono::duration_cast<chrono::seconds>(std::chrono::high_resolution_clock::now() - this->start).count() << " seconds |" << std::endl;
        this->current_k[1] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[1]);
        this->current_k[2] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[2]);
        return;
    }

    // x Z Z
    if (this->current_k[2] == 'Z' && this->current_k[1] == 'Z' && this->current_k[0] != 'Z') {
        std::cout << "Testing ENIGMA rotors [";
        std::cout << this->current_setting[0] << this->current_setting[1] << this->current_setting[2];
        std::cout << "] on iteration [" <<  26 << " * " << to_string((this->count)/26) << "] with rotation: [";
        std::cout << this->current_k[0] << this->current_k[1] << this->current_k[2];
        std::cout << "] \t \t | Time used: " << chrono::duration_cast<chrono::seconds>(std::chrono::high_resolution_clock::now() - this->start).count() << " seconds |" << std::endl;
        this->current_k[2] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[2]);
        this->current_k[1] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[1]);
        this->current_k[0] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->current_k[0]);
        return;
    }

    // Always turn the fastest rotor
//    std::cout << "Testing ENIGMA rotors [";
//    std::cout << this->current_setting[0] << this->current_setting[1] << this->current_setting[2];
//    std::cout << "] on iteration [" <<  26 << " * " << to_string((this->count)/26) << "] with rotation: [";
//    std::cout << this->current_k[0] << this->current_k[1] << this->current_k[2];
//    std::cout << "] \t \t | Time used: " << chrono::duration_cast<chrono::seconds>(std::chrono::high_resolution_clock::now() - this->start).count() << " seconds |" << std::endl;
    this->current_k[2] = Utilities::followPermutation({Utilities::getAlphabet()}, this->current_k[2]);
}

std::vector<char> AdvancedTuringBombe::increase_k(std::vector<char> cur_k) {
    if (cur_k[0] == 'Z' && cur_k[1] == 'Z' && cur_k[2] == 'Z') {
        // We have done a full rotation without any luck, cracking has failed :(
        throw std::exception();
    }

    // x x Z
    if (cur_k[2] == 'Z' && cur_k[1] != 'Z') {
        cur_k[1] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                cur_k[1]);
        cur_k[2] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                cur_k[2]);
        return cur_k;
    }

    // x Z Z
    if (cur_k[2] == 'Z' && cur_k[1] == 'Z' && cur_k[0] != 'Z') {
        cur_k[2] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                cur_k[2]);
        cur_k[1] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                cur_k[1]);
        cur_k[0] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                cur_k[0]);
        return cur_k;
    }

    // Always turn the fastest rotor
    cur_k[2] = Utilities::followPermutation({Utilities::getAlphabet()}, cur_k[2]);
    return cur_k;
}

void AdvancedTuringBombe::setup_gamma_for_cur_k() {
    this->gammaGraph->transitions.clear();
    // Setting up: (L_1, L_2) - (L_2, L_1)
    for (auto elemA: this->gammaGraph->nodes) {
        for (auto elemB: this->gammaGraph->nodes) {
            std::string full_a; full_a.push_back(elemA->letterA); full_a.push_back(elemA->letterB);
            std::string full_b; full_b.push_back(elemB->letterB); full_b.push_back(elemB->letterA);
            if (elemA != elemB && (full_a == full_b)) {
                std::pair<GammaNode*, GammaNode*> searchA{elemA, elemB};
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
        std::vector<GammaNode*> L1row = this->gammaGraph->getNodesWithALetter(L_1);
        std::vector<GammaNode*> L2row = this->gammaGraph->getNodesWithALetter(L_2);
        std::vector<char> copy_k(this->current_k);
        int transition_weight = std::get<2>(transition);
        for (int i = 0; i < transition_weight - 1; i++) {
            copy_k = AdvancedTuringBombe::increase_k(copy_k); // Increasing by the weight of l
        }
        for (auto L1_L3: L1row) {
            char L_3_letter = L1_L3->letterB; // Letter to use for sigma calculation on row L_2
            Enigma enigma(this->p0_perm,this->p1_perm, this->p2_perm, this->p3_perm, this->p4_perm,
                          {},
                          this->tau_perm,
                          {}, // should be empty no worries
                          this->current_setting,
                          copy_k
                          );
            char epsilonL_3 = enigma.encryptLetter(L_3_letter);
            for (auto & L2_eL3: L2row) {
                if (L2_eL3->letterB == epsilonL_3) {
                    std::pair<GammaNode*, GammaNode*> searchA{L1_L3, L2_eL3};
                    std::pair<GammaNode*, GammaNode*> searchB{L2_eL3, L1_L3};
                    bool inside = (std::find(this->gammaGraph->transitions.begin(), this->gammaGraph->transitions.end(),
                                             searchA) != this->gammaGraph->transitions.end());
                    inside = inside && (std::find(this->gammaGraph->transitions.begin(), this->gammaGraph->transitions.end(),
                                                  searchB) != this->gammaGraph->transitions.end());

                    if (!inside)
                        this->gammaGraph->transitions.emplace_back(L1_L3, L2_eL3);
                    break;
                }
            }
        }
    }
    // Fixing which nodes should be turned on and off
    for (auto & node: Utilities::getAlphabet()) {
        // Turn potential on (L_1, L_2) and following nodes
        this->gammaGraph->turnNodesConnectedOn(this->cribGraph->most_edges_node->letter,
                                               {node});
        bool result = this->check_permutation_graph();
        if (result) {
            std::cout << "SUCCESSSS!!!!" << std::endl;
            std::cout << "Setting: ";
            for (auto item: this->current_setting) {
                std::cout << item;
            } std::cout << std::endl;
            std::cout << "Current k: ";
            for (auto ch: this->current_k) {
                std::cout << ch;
            } std::cout << std::endl;
            std::vector<std::string> stekkerbord{};
            for (auto successNode: this->gammaGraph->nodes) {
                if (successNode->correct and successNode->letterB != successNode->letterA) {
                    std::string stekker;
                    stekker += successNode->letterA;
                    stekker += successNode->letterB;
                    std::reverse(stekker.begin(), stekker.end());
                    if (std::find(stekkerbord.begin(), stekkerbord.end(), stekker) == stekkerbord.end()) {
                        std::reverse(stekker.begin(), stekker.end());
                        stekkerbord.emplace_back(stekker);
                    }
                }
            }
            if (this->crib == "DEOPGAVEVOORENIGMA")
                stekkerbord.emplace_back("FU"); // TODO remove - found by brute force
            /*
             * FU not in crib graph, so not in original edges
             * after, it can only get turned on by UF or by itself, but FU and UF do not have any other transitions
             * (Since first (L_1, L_2) - (L_2, L_1) => This transition they have: (F, U) - (U, F))
             * (\forall (L1) -L- (L2)... They are not in the crib graph so they cannot every connect :(
             */
            Enigma enigma(this->p0_perm,this->p1_perm, this->p2_perm, this->p3_perm, this->p4_perm,
                          stekkerbord,
                          this->tau_perm,
                          {}, // should be empty no worries
                          this->current_setting,
                          this->current_k);
            std::cout << "SOLUTION: ";
            for (auto ch: this->code) {
                std::cout << enigma.encryptLetter(ch);
            }
            std::cout << std::endl;
            std::cout << "Plug board: ";
            for (const auto& ch: stekkerbord) {
                std::cout << " " << ch << " ";
            }
            exit(EXIT_SUCCESS);
        }
    }
}


