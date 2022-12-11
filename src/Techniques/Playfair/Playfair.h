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

    std::string simulatedAnnealing(int kMax);
    std::string simulatedAnnealing(int kMax, int max_misses);

    std::string decode(const std::string &config, const std::string &input);
    std::string encode(const std::string &config, const std::string &input);

private:

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

    double getFrequencyScore(const std::string& decoded);

    static void transform(const std::string &config, char &c1, char &c2, int sign);

    static double temperature(int k, int kMax);

    double energy(const std::string &config);
};


#endif //CODE_THEORY_PLAYFAIR_H
