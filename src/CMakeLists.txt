cmake_minimum_required(VERSION 3.20.2)
project(Code-Theory)

set(CMAKE_CXX_STANDARD 14)

set(GENERAL
        System/System.h
        System/System.cpp
        main.cpp)

set(ENIGMA
        Enigma/Enigma.cpp
        Enigma/Enigma.h)

set(PLAYFAIR
        Playfair/playfair.cpp
        Playfair/playfair.h)

set(VIGENEREPLUS
        VigenerePlus/Vigenere.h
        VigenerePlus/Vigenere.cpp)

add_executable(Enigma ${GENERAL} ${ENIGMA})
add_executable(Playfair ${GENERAL} ${PLAYFAIR})
add_executable(VigenerePlus ${GENERAL} ${VIGENEREPLUS})