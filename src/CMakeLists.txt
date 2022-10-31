cmake_minimum_required(VERSION 3.20.2)
project(Code-Theory)

set(CMAKE_CXX_STANDARD 14)

set(GENERAL
        System/System.h
        System/System.cpp
        main.cpp)

set(ENIGMA
        Techniques/Enigma/Enigma.cpp
        Techniques/Enigma/Enigma.h)

set(PLAYFAIR
        Techniques/Playfair/playfair.cpp
        Techniques/Playfair/playfair.h)

set(VIGENEREPLUS
        Techniques/VigenerePlus/Vigenere.h
        Techniques/VigenerePlus/Vigenere.cpp)

add_executable(Enigma ${GENERAL} ${ENIGMA})
add_executable(Playfair ${GENERAL} ${PLAYFAIR})
add_executable(VigenerePlus ${GENERAL} ${VIGENEREPLUS})