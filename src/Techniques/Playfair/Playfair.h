//
// Created by Robbe Nooyens on 17/11/2022.
//

#ifndef CODE_THEORY_PLAYFAIR_H
#define CODE_THEORY_PLAYFAIR_H


#include <string>
#include <map>
#include <random>
#include <algorithm>

class Playfair {
public:
    std::string simulatedAnnealing(const std::string& cipher, int kMax);
    std::string decode(const std::string &config, const std::string &input);
    std::string encode(const std::string &config, const std::string &input);

    double getFrequencyScore(const std::string& decoded);

    bool useMSE = false;

    static double getLogQTest(const std::string &decoded);
private:
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen = std::mt19937 (rd()); // seed the generator

    std::uniform_int_distribution<> firstIndex = std::uniform_int_distribution<>(0, 24);

    std::uniform_int_distribution<> secondIndex = std::uniform_int_distribution<>(1, 24);

    std::uniform_real_distribution<> move = std::uniform_real_distribution<>(0, 1);

    const std::map<char, double> letterFrequency = {
            {'a', 0.0812},
            {'b', 0.0149},
            {'c', 0.0271},
            {'d', 0.0432},
            {'e', 0.1202},
            {'f', 0.0230},
            {'g', 0.0203},
            {'h', 0.0592},
            {'i', 0.0741},
            {'k', 0.0069},
            {'l', 0.0398},
            {'m', 0.0261},
            {'n', 0.0695},
            {'o', 0.0768},
            {'p', 0.0182},
            {'q', 0.0011},
            {'r', 0.0602},
            {'s', 0.0628},
            {'t', 0.0910},
            {'u', 0.0288},
            {'v', 0.0111},
            {'w', 0.0209},
            {'x', 0.0017},
            {'y', 0.0211},
            {'z', 0.0007}
    };

    static void transform(const std::string &config, char &c1, char &c2, int sign);

    static double temperature(int k, int kMax);

    double energy(const std::string &config, const std::string &cipher);

    static double getIndexOfCoincidence(const std::string &decoded);

    static void swap(std::string &s, int index1, int index2);
};


#endif //CODE_THEORY_PLAYFAIR_H
