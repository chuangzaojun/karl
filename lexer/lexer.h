#ifndef KARL_LEXER_H
#define KARL_LEXER_H

#include <string>
#include "token.h"

class Lexer {
private:
    std::string src;
    int line;

    void skipWhiteSpace();

    void skipComment();

    void next(int n);

    bool test(std::string s);

    std::string nextString(int n);

    std::string scanInt();

    std::string scanIdentifier();

    void error();

public:
    Lexer(std::string _src);

    Token *nextToken();
};

#endif // KARL_LEXER_H
