cmake_minimum_required(VERSION 3.15)
project(untitled9)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")

add_executable(untitled9 main.cpp Command.cpp Command.h Interpreter.cpp Interpreter.h ex1.cpp ex1.h)
