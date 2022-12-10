//
// Created by Cédric Leclercq on 31/10/2022.
//

#ifndef CODE_THEORY_SYSTEM_H
#define CODE_THEORY_SYSTEM_H

#include <string>

class System {
public:
    /**
     * @brief Run Vigenere plus
     *
     * @arg part of vineger to run
     */
    static void runVigenerePlus(const std::string & arg = "all");
    /**
     * @brief Run Enigma
     */
    static void runEnigma();
    /**
     * @brief Run Playfair
     */
    static void runPlayfair();
};


#endif //CODE_THEORY_SYSTEM_H
