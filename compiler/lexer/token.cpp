#include "token.hpp"

namespace karl {
    Token::Token(TokenType _type, std::string _literal, int _line, int _column) {
        type = _type;
        literal = _literal;
        line = _line;
        column = _column;
    }
} // karl