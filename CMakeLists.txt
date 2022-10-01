cmake_minimum_required(VERSION 3.23)
project(karl)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(karl main.cpp lexer/lexer.h lexer/lexer.cpp lexer/token.h lexer/token.cpp ast/expr.h ast/expr.cpp ast/program.h ast/stmt.h ast/stmt.cpp parser/parser.h parser/parser.cpp evaluator/environment.cpp evaluator/environment.h object/object.cpp object/object.h evaluator/evaluator.cpp evaluator/evaluator.h)
