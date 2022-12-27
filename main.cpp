#include "compiler/parser/parser.hpp"
#include <vector>

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
                      "    while (i <= n) {\n"
                      "        i = i + 1;\n"
                      "        print(fib(i));\n"
                      "    }\n"
                      "}\n";
    Lexer *lexer = new Lexer(src);
    Parser *parser = new Parser(lexer);
    Program *program = parser->parseProgram();
    return 0;
}
