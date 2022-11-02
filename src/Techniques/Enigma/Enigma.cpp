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
        EnigmaNode * node1 = findInCribGraph(crib[i]);
        EnigmaNode * node2 = findInCribGraph(coded_message[i]);
        node1->edges_cost.emplace_back(node2, i+1);
        node2->edges_cost.emplace_back(node1, i+1);
        // Checking if coded text is linked back to crib
//        int index = static_cast<int>(coded_message.find(crib[i]));
//        if (0 <= index && index <= static_cast<int>(crib.size())) {
//            if (crib[index] == coded_message[index])
//                node2->edges_cost.emplace_back(node1, index);
//        }
    }
    std::cout << "DIKKE";
}

EnigmaNode *Enigma::findInCribGraph(char x) {
    for (auto elem: this->cribGraph) {
        if (elem->letter == x) {
            return elem;
        }
    }
    return nullptr;
}


