cmake_minimum_required(VERSION 3.15)
project(ex3Project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex3Project main.cpp cmake-build-debug/Command.cpp cmake-build-debug/Command.h cmake-build-debug/CMakeFiles/Interpreter.cpp cmake-build-debug/CMakeFiles/Interpreter.h)