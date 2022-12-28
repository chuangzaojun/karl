
#ifndef KARL_ERROR_HPP
#define KARL_ERROR_HPP

#include "../compiler/lexer/token.hpp"

namespace karl {

    void lexError(int line, int column);

    void grammarError(TokenType expectType, Token *readToken);

    void grammarError(Token *readToken);

    void varNotFound(std::string var, int line, int column);
} // karl

#endif //KARL_ERROR_HPP
