cmake_minimum_required(VERSION 3.23)
project(karl VERSION 0.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS)

add_executable(karl main.cpp compiler/parser/lexer/lexer.hpp compiler/parser/lexer/lexer.cpp compiler/parser/lexer/token.hpp compiler/parser/lexer/token.cpp compiler/error/error.cpp compiler/error/error.hpp compiler/ast/stmt.cpp compiler/ast/stmt.hpp compiler/ast/expr.cpp compiler/ast/expr.hpp compiler/ast/object_type.cpp compiler/ast/object_type.hpp compiler/parser/parser.cpp compiler/parser/parser.hpp compiler/ast/program.cpp compiler/ast/program.hpp compiler/type_checker/type_checker.cpp compiler/type_checker/type_checker.hpp compiler/ast/var_table.cpp compiler/ast/var_table.hpp compiler/ast/func_table.cpp compiler/ast/func_table.hpp bytecode/bytecode.hpp bytecode/instruction.cpp bytecode/instruction.hpp compiler/ast/expr.cpp bytecode/func_info.hpp  bytecode/bytecode.cpp bytecode/func_info.cpp compiler/generator/generator.hpp compiler/generator/generator.cpp vm/vm.cpp vm/vm.hpp vm/heap.cpp vm/heap.hpp vm/object.cpp vm/object.hpp vm/frame.cpp vm/frame.hpp shell/shell.cpp shell/shell.hpp)