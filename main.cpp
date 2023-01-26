#include "compiler/parser/parser.hpp"
#include "compiler/type_checker/type_checker.hpp"
#include "compiler/generator/generator.hpp"
#include "vm/vm.hpp"
#include <iostream>
#include <vector>
#include <map>

using namespace karl;

int main() {

    std::string src = "func main() : void {\n"
                      "    print(\"Hello, World!\\n\");\n"
                      "}\n";
    compiler::Lexer *lexer = new compiler::Lexer(src);
    compiler::Parser *parser = new compiler::Parser(lexer);
    compiler::Program *program = parser->parseProgram();
    compiler::TypeChecker *tc = new compiler::TypeChecker(program);
    tc->checkProgram();
    compiler::Generator *generator = new compiler::Generator(program);
    bytecode::Bytecode *bytecode = generator->generateBytecode();
    vm::VM *vm = new vm::VM(bytecode, new vm::Heap());
    vm->run();
    return 0;
}