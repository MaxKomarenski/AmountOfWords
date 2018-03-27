cmake_minimum_required(VERSION 3.6)
project(AmountOfWords)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Configuration.cpp Configuration.h)
add_executable(AmountOfWords ${SOURCE_FILES})