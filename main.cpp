#include "compiler/parser/parser.hpp"
#include "compiler/type_checker/type_checker.hpp"
#include <iostream>
#include <vector>
#include <map>

using namespace karl;

int main() {

    std::string src = "func fib(n: int) : int {\n"
                      "    if (n == 1 || n == 0) {\n"
                      "        return 1;\n"
                      "    }\n"
                      "    return fib(n - 1) + fib(n - 2);\n"
                      "}\n"
                      "\n"
                      "func main() : void {\n"
                      "    var a: int = 10, i: int = 0;\n"
                      "    while (i <= a) {\n"
                      "        i = i + 1;\n"
                      "        print(fib(i));\n"
                      "    }\n"
                      "}\n";
    Lexer *lexer = new Lexer(src);
    Parser *parser = new Parser(lexer);
    Program *program = parser->parseProgram();
    TypeChecker *tc = new TypeChecker(program);
    tc->checkProgram();
    return 0;
}