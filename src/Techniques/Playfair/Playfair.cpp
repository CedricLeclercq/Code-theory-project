//
// Created by Robbe Nooyens on 17/11/2022.
//

#include "Playfair.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>
#include <random>
#include <sstream>
#include <iostream>

#define HILLCLIMB_AMOUNT 10
#define HILLCLIMB_DEPTH 100

// nqbuthlmafekzivprwocyxdsg : 0299568

using namespace std;

double Playfair::getFrequencyScore(const string &decoded) {
    double score = 0;
    auto length = (double) decoded.length();
    for(auto const& [c, predicted]: letterFrequency) {
        double observed = (double) count(decoded.begin(), decoded.end(), c);
        observed /= length;
        score += pow(observed - predicted, 2);
//        score += abs(observed - predicted);
    }
    return score;
}

Playfair::Playfair(string  cipher): cipherText(move(cipher)) {}

void Playfair::decrypt() {
    // Construct a square 1000 times
    std::random_device random_dev;
    std::mt19937       generator(random_dev());
    std::vector<char> characters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'l', 'm', 'n', 'o', 'p','q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    double score = std::numeric_limits<double>::infinity();
    string config;
    for(int i = 0; i < HILLCLIMB_AMOUNT; i++) {
        shuffle(characters.begin(), characters.end(), generator);
        hillClimbing(characters, score, config);
        cout << i << ":\t" << score << " : " << config << endl;
    }
//    characters = vector<char>(config.begin(), config.end());
//    for(int i = 0; i < HILLCLIMB_AMOUNT; i++) {
//        hillClimbing(characters, score, config);
//        cout << i << ":\t" << score << " : " << config << endl;
//    }
    vector<char> solution(config.begin(), config.end());
    cout << decode(solution) << endl;
}

void Playfair::transform(const vector<char> &config, char &c1, char &c2, int sign) {
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

double Playfair::decodeScore(const vector<char> &config) {
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

string Playfair::decode(const vector<char> &config) {
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
    return decoded.str();
}

void Playfair::hillClimbing(std::vector<char> &charSeq, double &bestScore, string& bestConfig) {
    double score = this->decodeScore(charSeq);
    string config(charSeq.begin(), charSeq.end());
    for(int i = 0; i < HILLCLIMB_DEPTH; i++) {
        int index1 = rand() % (charSeq.size());
        int index2 = rand() % (charSeq.size());
        char temp = charSeq.at(index1);
        charSeq.at(index1) = charSeq.at(index2);
        charSeq.at(index2) = temp;
        double new_score = this->decodeScore(charSeq);
        if(new_score < score) {
            score = new_score;
            config = string(charSeq.begin(), charSeq.end());
        }
    }
    if(score < bestScore) {
        bestScore = score;
        bestConfig = config;
    }

}

