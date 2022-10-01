#include "parser/parser.h"
#include "evaluator/evaluator.h"
#include <fstream>

int main(int argc, char **args) {
    std::ifstream fin(args[1]);
    if (!fin.is_open()) {
        printf("file is not found\n");
    }
    std::string s, src;
    while (std::getline(fin,s)) {
        src += s + "\n";
    }
    fin.close();
    Lexer *lexer = new Lexer(src);
    Parser *parser = new Parser(lexer);
    Program *program = parser->parseProgram();
    Environment *environment = new Environment();
    Evaluator *evaluator = new Evaluator(environment);
    evaluator->evalProgram(program);
    return 0;
}
