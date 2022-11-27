cmake_minimum_required(VERSION 3.23)
project(karl VERSION 0.2)

set(CMAKE_CXX_STANDARD 20)

add_executable(karl main.cpp compiler/lexer/lexer.hpp compiler/lexer/lexer.cpp compiler/lexer/token.hpp compiler/lexer/token.cpp error/error.cpp error/error.hpp)