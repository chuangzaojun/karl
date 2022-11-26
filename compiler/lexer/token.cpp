#include "token.hpp"

namespace karl {
    Token::Token(TokenType _type, std::string _literal, int _line) {
        type = _type;
        literal = _literal;
        line = _line;
    }
} // karl