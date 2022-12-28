
#ifndef KARL_ERROR_HPP
#define KARL_ERROR_HPP

#include "../compiler/lexer/token.hpp"

namespace karl {

    void lexError(int line, int column);

    void grammarError(TokenType expectType, Token *readToken);

    void grammarError(Token *readToken);

    void varNotFoundError(std::string var, int line, int column);

    void varHasDefError(std::string var, int line, int column);

    void funcNotFoundError(std::string func, int line, int column);

    void funcHasDefError(std::string func, int line, int column);

    class TypeError {
        static void invalidStmt(int line, int column);
    };
} // karl

#endif //KARL_ERROR_HPP
