#ifndef KARL_TOKEN_H
#define KARL_TOKEN_H

#include <string>

enum TokenType {
    TOKEN_EOF, // end-of-file
    TOKEN_SEP_SEMI, // ;
    TOKEN_SEP_LPAREN, // (
    TOKEN_SEP_RPAREN, // )
    TOKEN_SEP_LCURLY, // {
    TOKEN_SEP_RCURLY, // }
    TOKEN_OP_ASSIGN, // =
    TOKEN_OP_MINUS, // -
    TOKEN_OP_ADD, // +
    TOKEN_OP_MUL, // *
    TOKEN_OP_DIV, // /
    TOKEN_OP_MOD, // %
    TOKEN_OP_LT, // <
    TOKEN_OP_LE, // <=
    TOKEN_OP_GT, // >
    TOKEN_OP_GE, // >=
    TOKEN_OP_EQ, // ==
    TOKEN_OP_NE, // !=
    TOKEN_OP_NOT, // !
    TOKEN_KW_ELSE, // else
    TOKEN_KW_FALSE, // false
    TOKEN_KW_IF, // if
    TOKEN_KW_TRUE, // true
    TOKEN_KW_WHILE, // while
    TOKEN_IDENTIFIER, // identifier
    TOKEN_INT, // int literal
};

class Token {
private:
    TokenType type;
    std::string value;
    int line;
public:
    Token(TokenType _type, std::string _value, int _line);

    TokenType getType();

    std::string getValue();

    int getLine();
};


#endif // KARL_TOKEN_H
