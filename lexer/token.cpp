
#include "token.h"

Token::Token(TokenType _type, std::string _value, int _line) {
    type = _type;
    value = _value;
    line = _line;
}

TokenType Token::getType() {
    return type;
}

std::string Token::getValue() {
    return value;
}

int Token::getLine() {
    return line;
}