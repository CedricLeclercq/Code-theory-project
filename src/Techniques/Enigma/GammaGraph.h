//
// Created by Cédric Leclercq on 08/12/2022.
//

#ifndef CODE_THEORY_GAMMAGRAPH_H
#define CODE_THEORY_GAMMAGRAPH_H

#include <vector>
#include <iostream>

struct GammaNode {
    char letterA; // X coordinate - Letters
    char letterB; // Y Coordinate - Sigma(letters)
    bool correct;
    GammaNode(char new_letterA, char new_letterB, bool correct) {
        this->letterA = new_letterA;
        this->letterB = new_letterB;
        this->correct = correct;
    }
};




struct GammaGraph {
    std::vector<GammaNode*> nodes;
    std::vector<std::pair<GammaNode*, GammaNode*>> transitions; // Node1, node2, true or false
    GammaGraph()=default;

    std::vector<GammaNode*> getNodesWithALetter(char letter) {
        std::vector<GammaNode*> result{};
        for (auto node: this->nodes) {
            if (node->letterA == letter)
                result.push_back(node);
        }
        return result;
    }
    std::vector<GammaNode*> getNodesWithBLetter(char letter) {
        std::vector<GammaNode*> result{};
        for (auto node: this->nodes) {
            if (node->letterB == letter)
                result.push_back(node);
        }
        return result;
    }

    void turnNodesOff() {
        for (auto node: this->nodes) {
            node->correct = false;
        }
    }

    void turnNodesConnectedOn(char initToSelect, const std::vector<char>& initToConnect) {
        // Turn all off
        this->turnNodesOff();
        // Turn (L_1, L_2) on
        for (auto ch: initToConnect) {
            for (auto node: this->nodes) {
                if (node->letterA == initToSelect && node->letterB == ch) {
                    node->correct = true;
                }
            }
        }
        bool new_updated = true;
        while (new_updated) {
            new_updated = false;

        }
    }
};


#endif //CODE_THEORY_GAMMAGRAPH_H
