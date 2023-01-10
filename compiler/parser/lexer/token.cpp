#include "token.hpp"

namespace karl::compiler {
    Token::Token(TokenType type, std::string literal, int line, int column) {
        this->type = type;
        this->literal = literal;
        this->line = line;
        this->column = column;
    }
} // karl