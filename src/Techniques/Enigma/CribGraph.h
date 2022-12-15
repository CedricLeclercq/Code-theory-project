//
// Created by Cédric Leclercq on 08/12/2022.
//

#ifndef CODE_THEORY_CRIBGRAPH_H
#define CODE_THEORY_CRIBGRAPH_H

#include <vector>
#include <string>
#include <algorithm>
#include "../../Utilities/Utilities.h"


struct CribNode {
    char letter;
    explicit CribNode(char new_letter) {this->letter = new_letter;}
};



struct CribGraph {
    std::string crib;
    std::string meaning;
    std::vector<CribNode*> nodes;
    CribNode * most_edges_node;
    char replaced_of_most_edge;
    std::vector<char> connectedWithMostEdges;
    std::vector<std::tuple<CribNode*, CribNode*, int>> transitions;

    explicit CribGraph(std::string crib, std::string meaning) {
        this->crib = std::move(crib);
        this->meaning = std::move(meaning);
        this->setupCribGraph();
        this->selectMostConnected();
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

    void selectMostConnected() {
        std::map<CribNode*, int> result;
        for (auto transition: this->transitions) {
            ++result[std::get<0>(transition)];
            ++result[std::get<1>(transition)];
        }

        this->most_edges_node =
                std::max_element(result.begin(), result.end(),[]
                (const pair<CribNode*,int>& p1, const pair<CribNode*, int>& p2) {
            return p1.second < p2.second;})->first;
        size_t location = this->crib.find(this->most_edges_node->letter);
        this->replaced_of_most_edge = this->meaning[location];

        for (auto transition: this->transitions) {
            if (std::get<0>(transition) == this->most_edges_node) {
                this->connectedWithMostEdges.push_back(std::get<1>(transition)->letter);
            }
            if (std::get<1>(transition) == this->most_edges_node) {
                this->connectedWithMostEdges.push_back(std::get<0>(transition)->letter);
            }
        }
    }
};

#endif //CODE_THEORY_CRIBGRAPH_H
