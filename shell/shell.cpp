#include "shell.hpp"
#include "../compiler/parser/parser.hpp"
#include "../compiler/type_checker/type_checker.hpp"
#include "../compiler/generator/generator.hpp"
#include "../vm/vm.hpp"
#include "iostream"
#include <fstream>
#include <sstream>

namespace karl {
    namespace shell {
        std::string read(std::string fileName) {
            std::ifstream in(fileName);
            if (in.is_open() == false) {
                printf("File not found.\n");
                exit(0);
            }
            std::stringstream buffer;
            buffer << in.rdbuf();
            return buffer.str() + "\n";
        }

        void run(std::vector<std::string> &args) {
            if (args.size() != 1) {
                printf("Invalid arguments.\n");
                exit(0);
            }
            std::string src = read(args[0]);
            compiler::Lexer *lexer = new compiler::Lexer(src);
            compiler::Parser *parser = new compiler::Parser(lexer);
            compiler::Program *program = parser->parseProgram();
            compiler::TypeChecker *tc = new compiler::TypeChecker(program);
            tc->checkProgram();
            compiler::Generator *generator = new compiler::Generator(program);
            bytecode::Bytecode *bytecode = generator->generateBytecode();
//            std::cout << bytecode->toString();
            vm::VM *vm = new vm::VM(bytecode, new vm::Heap());
            vm->run();
        }
    }
}