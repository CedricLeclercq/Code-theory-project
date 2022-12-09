//
// Created by Robbe Nooyens on 17/11/2022.
//

#include "Playfair.h"
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
#include <random>
#include <sstream>
#include <iostream>

#define HILLCLIMB_AMOUNT 100
#define HILLCLIMB_DEPTH 10000

// nqbuthlmafekzivprwocyxdsg : 0299568

using namespace std;

double Playfair::getFrequencyScore(const string &decoded) {
    double score = 0;
    auto length = (double) decoded.length();
    for(auto const& frequency: letterFrequency) {
        double observed = (double) count(decoded.begin(), decoded.end(), frequency.first);
        observed /= length;
//        score += pow(observed - predicted, 2);
        score += abs(observed - frequency.second);
    }
    return score;
}

Playfair::Playfair(string  cipher): cipherText(move(cipher)) {}

void Playfair::decrypt() {
    // Construct a square 1000 times
    std::random_device random_dev;
    std::mt19937       generator(random_dev());
    string characters = "abcdefghiklmnopqrstuvwxyz";
    double score = std::numeric_limits<double>::infinity();
    string config;
    for(int i = 0; i < HILLCLIMB_AMOUNT; i++) {
        shuffle(characters.begin(), characters.end(), generator);
        hillClimbing(characters, score, config);
        cout << i << ":\t" << score << " : " << config << endl;
    }
    cout << decode(characters) << endl;
}

void Playfair::transform(const string &config, char &c1, char &c2, int sign) {
    auto it = find(config.begin(), config.end(), c1);
    assert(it != config.end());
    int index1 = it - config.begin();
    it = find(config.begin(), config.end(), c2);
    assert(it != config.end());
    int index2 = it - config.begin();
    int row1 = index1/5, col1 = index1%5;
    int row2 = index2/5, col2 = index2%5;
    assert(!(row1 == row2 && col1 == col2));
    if (row1 == row2) {
        col1 = (col1+sign+5)%5;
        col2 = (col2+sign+5)%5;
    } else if (col1 == col2) {
        row1 = (row1+sign+5)%5;
        row2 = (row2+sign+5)%5;
    } else {
        int tempcol = col1;
        col1 = col2;
        col2 = tempcol;
    }
    index1 = row1*5+col1;
    index2 = row2*5+col2;
    c1 = config.at(index1);
    c2 = config.at(index2);
}

double Playfair::decodeScore(string &config) {
    stringstream decoded;
    bool digram = false, potential_double = false;
    char c1, c2, doubled;
    for (char const &c: this->cipherText) {
        if (!digram) {
            c1 = c;
            digram = true;
        } else {
            c2 = c;
            digram = false;
            transform(config, c1, c2, -1);
            if (potential_double) {
                if(c1 == doubled) {
                    decoded << c1;
                } else {
                    decoded << c1 << 'x';
                }
            }
            if (c2 == 'x') {
                doubled = c1;
                potential_double = true;
            } else {
                decoded << c1 << c2;
            }
        }
    }
    return this->getFrequencyScore(decoded.str());
}

string Playfair::decode(const string &config) {
    stringstream decoded;
    bool digram = false;
    bool potential_double = false;
    char c1, c2, doubled;
    for (char const c: this->cipherText) {
        if (!digram) {
            c1 = c;
            digram = true;
        } else {
            c2 = c;
            digram = false;
            transform(config, c1, c2, -1);
            if (potential_double) {
                if(c1 == doubled) {
                    decoded << c1;
                } else {
                    decoded << c1 << 'x';
                }
            }
            if (c2 == 'x') {
                doubled = c1;
                potential_double = true;
            } else {
                decoded << c1 << c2;
            }
        }
    }
    return decoded.str();
}

void Playfair::hillClimbing(string &charSeq, double &bestScore, string& bestConfig) {
    double score = this->decodeScore(charSeq);
    string config(charSeq.begin(), charSeq.end());
    srand((unsigned) time(nullptr));
    int improve_timer = 0;
    for(int i = 0; i < HILLCLIMB_DEPTH; i++, improve_timer++) {
//        if(improve_timer > 100) {
////            cout << i << endl;
//            break;
//        }
        int index1 = rand() % (charSeq.size());
        int index2 = rand() % (charSeq.size());
        char temp = charSeq.at(index1);
        charSeq.at(index1) = charSeq.at(index2);
        charSeq.at(index2) = temp;
        double new_score = this->decodeScore(charSeq);
        if(new_score < score) {
            improve_timer = 0;
            score = new_score;
            config = string(charSeq.begin(), charSeq.end());
        }
    }
    if(score < bestScore) {
        bestScore = score;
        bestConfig = config;
    }

}

double Playfair::energy(const string& config) {
    return getFrequencyScore(decode(config));
}

double Playfair::temperature(int k, int kMax) {
    return 1-((double) k/(double) kMax);
}

string Playfair::simulatedAnnealing(int kMax) {
    string s = "abcdefghiklmnopqrstuvwxyz";
    // Randomness
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> firstIndex(0, 25);
    std::uniform_int_distribution<> secondIndex(1, 25);
    std::uniform_real_distribution<> move(0, 1);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int k = 0; k < kMax; k++) {
        string s_next = s;
        double T = temperature(k, kMax);
        int randIndex = firstIndex(gen);
        int randIndex2 = (randIndex + secondIndex(gen)) % 25;
        std::swap(s_next[randIndex], s_next[randIndex2]);
        double dE = energy(s) - energy(s_next);
        // Calculate probability
        double P;
        if(dE < 0) {
            P = 1;
        } else if(T == 0) {
            P = 0;
        } else {
            P = expf((float) -(dE/T));
        }
        if(P >= move(gen)) {
            s = string(s_next);
        }
        if(k % 50000 == 0) {
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            cout << "K: " << k << "\tT: " << T << "\tE:" << energy(s) << "\tS:" << s;
            cout << "\tTime: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << endl;
        }
    }
    return s;



}

