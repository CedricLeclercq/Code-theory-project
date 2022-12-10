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
        for (auto & node: this->nodes) {
            node->correct = false;
        }
    }

    void turnNodesConnectedOn(char initToSelect, std::vector<char> initToConnect) {
        // Turn all off
        this->turnNodesOff();
        //  TODO Debugging
//        this->nodes.clear();
//        this->transitions.clear();
//        auto * one = new GammaNode('A','A',false);
//        auto * two = new GammaNode('A','B',false);
//        auto * three = new GammaNode('A','C',false);
//        auto * four = new GammaNode('B','A',false);
//        auto * five = new GammaNode('B','B',false);
//        auto * six = new GammaNode('B','C',false);
//        auto * seven = new GammaNode('C','A',false);
//        auto * eight = new GammaNode('C','B',false);
//        auto * nine = new GammaNode('C','C',false);
//        this->nodes = {one, two, three, four, five, six, seven, eight, nine};
//        this->transitions.emplace_back(one, two);
//        this->transitions.emplace_back(three, four);
//        this->transitions.emplace_back(four, six);
//        initToSelect = 'A';
//        initToConnect = {'B','C'}; // AB true and AC true
        // TODO end Debugging
        // Turn (L_1, L_2) on
        for (auto ch: initToConnect) {
            for (auto &node: this->nodes) {
                if (node->letterA == initToSelect && node->letterB == ch) {
                    node->correct = true;
                }
            }
        }
        bool new_updated = true;
        while (new_updated) {
            new_updated = false;
            for (auto &transition: this->transitions) {
                if (transition.first->correct and not transition.second->correct) {
                    transition.second->correct = true;
                    new_updated = true;
                }
                if (transition.second->correct and not transition.first->correct) {
                    transition.first->correct = true;
                    new_updated = true;
                }
            }
        }
    }
};


#endif //CODE_THEORY_GAMMAGRAPH_H
