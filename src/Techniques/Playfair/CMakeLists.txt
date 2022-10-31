cmake_minimum_required(VERSION 3.23)
project(Playfair)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS} -O3 -pthread")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS} -O3 -pthread")

set(CMAKE_CXX_STANDARD 14)

add_executable(Playfair main.cpp playfair.cpp playfair.h)
