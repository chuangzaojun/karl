
#include "error.hpp"
#include <iostream>
#include <map>

namespace karl {
    void lexError(int line, int column) {
        printf("Unknown token at line %d, column %d.\n", line, column);
        exit(0);
    }

    void grammarError(TokenType expectType, Token *readToken) {
        std::map<TokenType, std::string> typeName = {
            {} // todo
        };
        printf("Unmatched token at line %d, column %d, expect \"%s\".\n", readToken->line, readToken->column, )
        exit(0);
    }

    void grammarError(Token *readToken) {
        printf("Unmatched token at line %d, column %d", readToken->line, readToken->column);
        exit(0);
    }
} // karl