#include "compiler/lexer/lexer.hpp"
#include <vector>

using namespace karl;

int main() {
    Lexer *l = new Lexer("\"......\"\n"
                         "123\n"
                         "' '\n"
                         "{[()]}\n"
                         "if else for func\n"
                         "jdd\n");
    std::vector<Token *> tokens;
    for (int i = 1; i <= 20; i++) {
        tokens.push_back(l->nextToken());
    }
    return 0;
}
