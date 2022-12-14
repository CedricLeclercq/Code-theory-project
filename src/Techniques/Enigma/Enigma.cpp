//
// Created by Cédric Leclercq on 30/11/2022.
//

#include "Enigma.h"
#include "../../Utilities/Utilities.h"
#include <string>
#include <algorithm>

Enigma::Enigma(std::vector<std::string> p0, std::vector<std::string> p1, std::vector<std::string> p2,
               std::vector<std::string> p3, std::vector<std::string> p4, std::vector<std::string> sigma,
               std::vector<std::string> tau, std::vector<std::string> pi, std::vector<int> rotor_setting,
               std::vector<char> cur_pos) {
    this->p0_perm = std::move(p0);
    this->p1_perm = std::move(p1);
    this->p2_perm = std::move(p2);
    this->p3_perm = std::move(p3);
    this->p4_perm = std::move(p4);
    this->sigma_perm = std::move(sigma);
    this->tau_perm = std::move(tau);
    this->pi_perm = std::move(pi);
    this->rotor_choice = std::move(rotor_setting);
    this->cur_position = std::move(cur_pos);
}

char Enigma::encryptLetter(const char &ch) {
//    if (ch == 'A') {
//        std::cout << "here" << std::endl;
//    }

    char result{};
    // Plug board - in
    char prev = ch;
    result = Utilities::followPermutation(this->sigma_perm, ch);
    // Plug board - out
    // Rotors - in
    int it = -1;
    reverse(this->rotor_choice.begin(), this->rotor_choice.end());
    reverse(this->cur_position.begin(), this->cur_position.end());
    for (int iterator : this->rotor_choice) {
        it += 1;
        switch (iterator) {
            default:
                throw std::exception();
            case 0: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::followPermutation(this->p0_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
            case 1: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::followPermutation(this->p1_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
            case 2: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::followPermutation(this->p2_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
            case 3: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::followPermutation(this->p3_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
            case 4: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::followPermutation(this->p4_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
        }
    }
    reverse(this->rotor_choice.begin(), this->rotor_choice.end());
    reverse(this->cur_position.begin(), this->cur_position.end());
    // Rotors - out
    // Reflector - in
    result = Utilities::followPermutation(this->tau_perm,result);
    // Reflector - out
    // Rotors (reverse) - in
    it = -1;
    for (int iterator : this->rotor_choice) {
        it += 1;
        switch (iterator) {
            default:
                throw std::exception();
            case 0: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::InverseFollowPermutation(this->p0_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
            case 1: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::InverseFollowPermutation(this->p1_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
            case 2: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::InverseFollowPermutation(this->p2_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
            case 3: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::InverseFollowPermutation(this->p3_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
            case 4: {
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, Utilities::getAlphabet().find(this->cur_position[it]));
                result = Utilities::InverseFollowPermutation(this->p4_perm, result);
                result = Utilities::cyclometric_continuation(Utilities::getAlphabet(), result, -(Utilities::getAlphabet().find(this->cur_position[it])));
                break;
            }
        }
    }
    // Rotors (reverse) - out
    // Plug board (reverse) - in
    prev = result;
    result = Utilities::InverseFollowPermutation(this->sigma_perm, result);
    // Plug board (reverse) - out
    // Rotate rotors of Enigma - in
    this->rotateRotors();
    // Rotate rotors of Engima - out
    // DONE
    return result;
}

void Enigma::rotateRotors() {
    this->rotations += 1;
    //std::cout << this->cur_position[0] << this->cur_position[1] << this->cur_position[2] << std::endl;
    // x x Z
    if (this->cur_position[2] == 'Z' && this->cur_position[1] != 'Z') {

        this->cur_position[1] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->cur_position[1]);
        this->cur_position[2] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->cur_position[2]);
        return;
    }

    // x Z Z
    if (this->cur_position[2] == 'Z' && this->cur_position[1] == 'Z') {
        this->cur_position[2] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->cur_position[2]);
        this->cur_position[1] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->cur_position[1]);
        this->cur_position[0] = Utilities::followPermutation({Utilities::getAlphabet()},
                                                          this->cur_position[0]);
        return;
    }


    // Always turn the fastest rotor
    this->cur_position[2] = Utilities::followPermutation({Utilities::getAlphabet()}, this->cur_position[2]);

//    if (this->cur_position[1] == 'Z') {
//        this->cur_position[0] = Utilities::followPermutation({Utilities::getAlphabet()},
//                                                             this->cur_position[0]);
//    }
//    if (this->cur_position[2] == 'Z') {
//        this->cur_position[1] = Utilities::followPermutation({Utilities::getAlphabet()},
//                                                             this->cur_position[1]);
//
//    }
//
//    // Always turn the fastest rotor
//    this->cur_position[2] = Utilities::followPermutation({Utilities::getAlphabet()},
//                                                             this->cur_position[2]);


}




