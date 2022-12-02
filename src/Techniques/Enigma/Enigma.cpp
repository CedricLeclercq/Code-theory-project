//
// Created by Cédric Leclercq on 30/10/2022.
//

#include "Enigma.h"

#include <utility>
#include <cassert>
#include <iostream>

using namespace std;

Enigma::Enigma(std::vector<std::string> newRotors, std::string newReflector, std::string newCrib, std::string code) {
    this->coded_message = std::move(code);
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
    this->setup_cribGraph();
    this->setup_raster();

    /*
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (auto x_letter: alphabet) {
        vector<EnigmaNode*> row{};
        for (auto y_letter: alphabet) {
            auto * node = new EnigmaNode(x_letter, y_letter, false);
            row.push_back(node);
        }
        this->cribGraph.push_back(row);
    }
     */
}

void Enigma::setup_cribGraph() {
    // Creating all the nodes and saving them
    for (auto letter: this->alphabet) {
        auto * node = new EnigmaNode(letter);
        this->cribGraph.push_back(node);
    }
    // Setting up edges for crib
    for (int i = 0; i < crib.size(); i++) {
        // Adding link to first node
        EnigmaNode * node1 = findInVectorGraph(crib[i], this->cribGraph);
        EnigmaNode * node2 = findInVectorGraph(coded_message[i], this->cribGraph);
        if (node1 == nullptr || node2 == nullptr) {
            std::cerr << "node cannot be found - Enigma.cpp - setup_cribGraph()" << std::endl;
            throw (exception()); // should never happen
        }
        node1->edges_cost.emplace_back(node2, i+1);
        node2->edges_cost.emplace_back(node1, i+1);

    }
}

EnigmaNode *Enigma::findInVectorGraph(char x, const vector<EnigmaNode*>& graph) {
    for (auto elem: graph) {
        if (elem->letter == x) {
            return elem;
        }
    }
    return nullptr;
}

void Enigma::setup_raster() {
    for (int i = 0; i < this->alphabet.size(); i++) {
        std::vector<bool> letter_vector{};
        for (int j = 0; j < this->alphabet.size(); j++) {
            letter_vector.push_back(false);
        }
        this->rasterPlugboard.push_back(letter_vector);
    }
}

void Enigma::setup_gamma_kGraph() {
    for (auto letter: this->alphabet) {
        auto * node = new EnigmaNode(letter);
        auto * node2 = new EnigmaNode(letter);
        cribGraph.push_back(node);
        cribGraph.push_back(node2);
    }
    // Adding edges (L_1, L_2) --- (L_2, L_1)
    for (auto letterA: this->alphabet) {
        for (auto letterB: this->alphabet) {
            EnigmaNode * L_1 = this->findInVectorGraph(letterA, this->gamma_kGraph);
            EnigmaNode * L_2 = this->findInVectorGraph(letterB, this->gamma_kGraph);
            L_1->edges_cost.emplace_back(L_2, 0);
            L_2->edges_cost.emplace_back(L_1, 0);
        }
    }

}

std::string Enigma::encrypt_letter(const char &ch) {
    // First go through plug board
    // Then go through the rotors
    // Then reflector
    // Then go through the rotors
    // Then go through plug board
    // Return
    return std::string();
}


