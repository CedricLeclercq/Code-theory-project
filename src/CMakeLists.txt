cmake_minimum_required(VERSION 3.20.2)
project(Code-Theory)

set(CMAKE_CXX_STANDARD 14)

set(GENERAL
        System/System.h
        System/System.cpp
        main.cpp)

set(Techniques/Enigma
        Techniques/Enigma/Enigma.cpp
        Techniques/Enigma/Enigma.h)

set(Techniques/Playfair
        Techniques/Playfair/playfair.cpp
        Techniques/Playfair/playfair.h)

set(Techniques/VigenerePlus
        Techniques/VigenerePlus/Vigenere.h
        Techniques/VigenerePlus/Vigenere.cpp)

add_executable(Techniques/Enigma ${GENERAL} ${ENIGMA})
add_executable(Techniques/Playfair ${GENERAL} ${PLAYFAIR})
add_executable(Techniques/VigenerePlus ${GENERAL} ${VIGENEREPLUS})