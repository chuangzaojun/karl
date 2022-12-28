cmake_minimum_required(VERSION 3.23)
project(karl VERSION 0.2)

set(CMAKE_CXX_STANDARD 20)

add_executable(karl main.cpp compiler/lexer/lexer.hpp compiler/lexer/lexer.cpp compiler/lexer/token.hpp compiler/lexer/token.cpp error/error.cpp error/error.hpp compiler/ast/stmt.cpp compiler/ast/stmt.hpp compiler/ast/expr.cpp compiler/ast/expr.hpp compiler/ast/object_type.cpp compiler/ast/object_type.hpp compiler/parser/parser.cpp compiler/parser/parser.hpp compiler/ast/program.cpp compiler/ast/program.hpp compiler/type_checker/type_checker.cpp compiler/type_checker/type_checker.hpp compiler/ast/var_table.cpp compiler/ast/var_table.hpp compiler/ast/func_table.cpp compiler/ast/func_table.hpp)