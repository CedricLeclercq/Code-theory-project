//
// Created by Robbe Nooyens on 17/11/2022.
//

#ifndef CODE_THEORY_PLAYFAIR_H
#define CODE_THEORY_PLAYFAIR_H


#include <string>
#include <map>

class Playfair {
public:
    explicit Playfair(std::string  cipher);

    void decrypt();
    std::string simulatedAnnealing(int kMax);

private:

    double getFrequencyScore(const std::string& decoded);
    const std::string cipherText;

    const std::map<char, double> letterFrequency = {
            {'a', 0.0849},
            {'b', 0.0207},
            {'c', 0.0453},
            {'d', 0.0338},
            {'e', 0.1116},
            {'f', 0.0181},
            {'g', 0.0247},
            {'h', 0.0300},
            {'i', 0.0774},
            {'k', 0.0110},
            {'l', 0.0548},
            {'m', 0.0301},
            {'n', 0.0665},
            {'o', 0.0716},
            {'p', 0.0316},
            {'q', 0.0019},
            {'r', 0.0758},
            {'s', 0.0573},
            {'t', 0.0695},
            {'u', 0.0363},
            {'v', 0.0100},
            {'w', 0.0128},
            {'x', 0.0029},
            {'y', 0.0177},
            {'z', 0.0027}
    };

    static void transform(const std::string &config, char &c1, char &c2, int sign);

    double decodeScore(std::string &config);

    void hillClimbing(std::string &charSeq, double &bestScore, std::string &bestConfig);

    std::string decode(const std::string &config);

    double temperature(int k, int kMax);

    double energy(const std::string &config);
};


#endif //CODE_THEORY_PLAYFAIR_H
