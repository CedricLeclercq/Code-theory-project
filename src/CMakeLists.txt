cmake_minimum_required(VERSION 3.20.2)
project(Code-Theory)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}") # -O3 -pthread
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS} -O3") #-O3 -pthread

set(GENERAL
        System/System.h
        System/System.cpp
        Utilities/Utilities.h
        Utilities/Utilities.cpp
        main.cpp)

set(ENIGMA
        Techniques/Enigma/Enigma.cpp
        Techniques/Enigma/Enigma.h
        Techniques/Enigma/AdvancedTuringBombe.cpp
        Techniques/Enigma/AdvancedTuringBombe.h
        Techniques/Enigma/GammaGraph.h
        Techniques/Enigma/CribGraph.h)
set(PLAYFAIR
        Techniques/Playfair/Playfair.cpp
        Techniques/Playfair/Playfair.h)

set(VIGENEREPLUS
        Techniques/VigenerePlus/Vigenere.h
        Techniques/VigenerePlus/Vigenere.cpp)

set(VIGENEREPLUS
        Techniques/VigenerePlus/Vigenere.h
        Techniques/VigenerePlus/Vigenere.cpp)

set(ADFGVX
        Techniques/adfgvx/adfgvx.h
        Techniques/adfgvx/adfgvx.cpp)

# add_executable(Enigma ${ENIGMA})
add_executable(System ${GENERAL} ${ENIGMA} ${PLAYFAIR} ${VIGENEREPLUS} ${ADFGVX} ${UTILITIES})
# add_executable(VigenerePlus ${VIGENEREPLUS})