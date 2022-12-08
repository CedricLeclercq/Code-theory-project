//
// Created by Cédric Leclercq on 08/12/2022.
//

#ifndef CODE_THEORY_GAMMAGRAPH_H
#define CODE_THEORY_GAMMAGRAPH_H

#include <vector>

struct GammaNode {
    char letterA;
    char letterB;
    GammaNode(char new_letterA, char new_letterB) {
        this->letterA = new_letterA;
        this->letterB = new_letterB;
    }
};




struct GammaGraph {
    std::vector<GammaNode*> nodes;
    std::vector<std::pair<GammaNode*, GammaNode*>> transitions;
    GammaGraph()=default;
};


#endif //CODE_THEORY_GAMMAGRAPH_H
