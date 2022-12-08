//
// Created by Cédric Leclercq on 08/12/2022.
//

#ifndef CODE_THEORY_GAMMAGRAPH_H
#define CODE_THEORY_GAMMAGRAPH_H

#include <vector>

struct GammaNode {
    char letterA; // X coordinate
    char letterB; // Y Coordinate
    GammaNode(char new_letterA, char new_letterB) {
        this->letterA = new_letterA;
        this->letterB = new_letterB;
    }
};




struct GammaGraph {
    std::vector<GammaNode*> nodes;
    std::vector<std::tuple<GammaNode*, GammaNode*, bool>> transitions; // Node1, node2, true or false
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
};


#endif //CODE_THEORY_GAMMAGRAPH_H