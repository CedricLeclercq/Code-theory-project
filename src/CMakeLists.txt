cmake_minimum_required(VERSION 3.20.2)
project(Code-Theory)

set(CMAKE_CXX_STANDARD 14)

set(GENERAL
        System/System.h
        System/System.cpp
        Utilities/Utilities.h
        Utilities/Utilities.cpp
        main.cpp)

set(ENIGMA
        Techniques/Enigma/Enigma.cpp
        Techniques/Enigma/Enigma.h
        Techniques/Enigma/EnigmaNode.cpp
        Techniques/Enigma/EnigmaNode.h)
set(PLAYFAIR
        Techniques/Playfair/Playfair.cpp
        Techniques/Playfair/Playfair.h)

set(VIGENEREPLUS
        Techniques/VigenerePlus/Vigenere.h
        Techniques/VigenerePlus/Vigenere.cpp)

set(UTILITIES
        Utilities/Utilities.h
        Utilities/Utilities.cpp)

# add_executable(Enigma ${ENIGMA})
add_executable(System ${GENERAL} ${ENIGMA} ${PLAYFAIR} ${VIGENEREPLUS} ${UTILITIES})
# add_executable(VigenerePlus ${VIGENEREPLUS})