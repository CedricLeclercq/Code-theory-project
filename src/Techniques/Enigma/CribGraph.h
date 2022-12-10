//
// Created by Cédric Leclercq on 08/12/2022.
//

#ifndef CODE_THEORY_CRIBGRAPH_H
#define CODE_THEORY_CRIBGRAPH_H

#include <vector>
#include <string>
#include "../../Utilities/Utilities.h"


struct CribNode {
    char letter;
    explicit CribNode(char new_letter) {this->letter = new_letter;}
};



struct CribGraph {
    std::string crib;
    std::string meaning;
    std::vector<CribNode*> nodes;
    std::vector<std::tuple<CribNode*, CribNode*, int>> transitions;

    explicit CribGraph(std::string crib, std::string meaning) {
        this->crib = std::move(crib);
        this->meaning = std::move(meaning);
        this->setupCribGraph();
    }

    CribNode * findCharNodeInGraph(char letter) {
        for (auto elem: this->nodes) {
            if (elem->letter == letter)
                return elem;
        }
        return nullptr;
    };

    void setupCribGraph() {
        std::string alphabet = Utilities::getAlphabet();
        // Setting up all the nodes
        for (auto letter: alphabet) {
            auto * node = new CribNode(letter);
            this->nodes.push_back(node);
        }
        // Setting up all transitions
        for (int i = 0; i < this->crib.size(); i++) {
            CribNode * one = this->findCharNodeInGraph(this->crib[i]);
            CribNode * two = this->findCharNodeInGraph(this->meaning[i]);
            this->transitions.emplace_back(one, two, i+1);
        }

    }
};

#endif //CODE_THEORY_CRIBGRAPH_H
