//
// Created by Cédric Leclercq on 02/11/2022.
//

#ifndef CODE_THEORY_ENIGMANODE_H
#define CODE_THEORY_ENIGMANODE_H

#include <string>
#include <vector>

class EnigmaNode {
public:
    char letter{};
    std::vector<std::pair<EnigmaNode*, int>> edges_cost{};

    EnigmaNode()=default;
    explicit EnigmaNode(char new_letter) {
        letter=new_letter;
    }

};


#endif //CODE_THEORY_ENIGMANODE_H
