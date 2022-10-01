#include "lexer.h"
#include <iostream>
#include <map>
#include <set>


std::map<std::string, TokenType> keywords = {
    {"else",  TOKEN_KW_ELSE},
    {"false", TOKEN_KW_FALSE},
    {"if",    TOKEN_KW_IF},
    {"true",  TOKEN_KW_TRUE},
    {"while", TOKEN_KW_WHILE}
};

std::map<std::string, TokenType> operators = {
    {";",  TOKEN_SEP_SEMI},
    {"(",  TOKEN_SEP_LPAREN},
    {")",  TOKEN_SEP_RPAREN},
    {"{",  TOKEN_SEP_LCURLY},
    {"}",  TOKEN_SEP_RCURLY},
    {"=",  TOKEN_OP_ASSIGN},
    {"-",  TOKEN_OP_MINUS},
    {"+",  TOKEN_OP_ADD},
    {"*",  TOKEN_OP_MUL},
    {"/",  TOKEN_OP_DIV},
    {"%",  TOKEN_OP_MOD},
    {"<",  TOKEN_OP_LT},
    {"<=", TOKEN_OP_LE},
    {">",  TOKEN_OP_GT},
    {">=", TOKEN_OP_GE},
    {"==", TOKEN_OP_EQ},
    {"!=", TOKEN_OP_NE},
    {"!",  TOKEN_OP_NOT}
};


std::set<char> simpleOperators = {
    ';', '(', ')', '{', '}', '=', '-', '+', '*', '/', '%', '<', '>', '!'
};

bool isWhiteSpace(char c) {
    return c == '\t' || c == '\v' || c == '\f' || c == ' ';
}

bool isNewLine(char c) {
    return c == '\r' || c == '\n';
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

Lexer::Lexer(std::string _src) {
    src = _src;
    line = 1;
}

Token *Lexer::nextToken() {
    skipWhiteSpace();
    if (src.size() == 0) {
        return new Token(TOKEN_EOF, "EOF", line);
    }
    if (simpleOperators.count(src[0])) {
        if (operators.count(nextString(2))) {
            std::string op = nextString(2);
            next(2);
            return new Token(operators[op], op, line);
        }
        std::string op = nextString(1);
        next(1);
        return new Token(operators[op], op, line);
    }
    if (isDigit(src[0])) {
        return new Token(TOKEN_INT, scanInt(), line);
    }
    if (isLetter(src[0]) || src[0] == '_') {
        std::string ident = scanIdentifier();
        if (keywords.count(ident)) {
            return new Token(keywords[ident], ident, line);
        }
        return new Token(TOKEN_IDENTIFIER, ident, line);
    }
    error();
    return NULL;
}

void Lexer::error() {
    printf("unknown token at line %d\n", line);
    exit(0);
}

std::string Lexer::scanInt() {
    std::string s;
    while (isDigit(src[0])) {
        s += src[0];
        next(1);
    }
    return s;
}

std::string Lexer::scanIdentifier() {
    std::string s;
    while (isLetter(src[0]) || isDigit(src[0]) || src[0] == '_') {
        s += src[0];
        next(1);
    }
    return s;
}

void Lexer::next(int n) {
    src = src.substr(n);
}

std::string Lexer::nextString(int n) {
    return src.substr(0, n);
}

bool Lexer::test(std::string s) {
    return s == src.substr(0, s.size());
}

void Lexer::skipComment() {
    if (test("//")) {
        while ((!isNewLine(src[0])) && src.size() > 0) {
            next(1);
        }
    }
}

void Lexer::skipWhiteSpace() {
    while (src.size() > 0) {
        if (test("\r\n") || test("\n\r")) {
            next(2);
            line++;
        } else if (isNewLine(src[0])) {
            next(1);
            line++;
        } else if (test("//")) {
            skipComment();
        } else if (isWhiteSpace(src[0])) {
            next(1);
        } else {
            break;
        }
    }
}