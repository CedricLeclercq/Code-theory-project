//
// Created by Robbe Nooyens on 30/10/2022.
//

#ifndef PLAYFAIR_PLAYFAIR_H
#define PLAYFAIR_PLAYFAIR_H

//void encode(const std::string &config, char &c1, char &c2);
//void decode(const std::string &config, char &c1, char &c2);

void decode(const std::string &config, const std::string& input, std::stringstream &decoded);

std::string encrypt(std::string text, const std::string &key);
void decrypt(const std::string &text, std::vector<std::string> &dutch, std::vector<std::string> &english, std::vector<std::string> &french, std::vector<std::string> &german, std::vector<std::string> &spanish);

#endif //PLAYFAIR_PLAYFAIR_H
