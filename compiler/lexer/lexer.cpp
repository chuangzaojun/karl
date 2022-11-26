#include "lexer.hpp"
#include <map>

namespace karl {

    std::map<std::string, TokenType> keywords = {
        {"true", TokenType::True},
        {"false", TokenType::False},
        {"var", TokenType::Var},
        {"func", TokenType::Func},
        {"if", TokenType::If},
        {"elif", TokenType::Elif},
        {"else", TokenType::Else},
        {"while", TokenType::While},
        {"int", TokenType::Int},
        {"bool", TokenType::Bool},
        {"string", TokenType::String},
        {"char", TokenType::Char},
        {"void", TokenType::Void}
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
        column = 1;
        pos = 0;
    }

    void Lexer::next(int n) {
        pos += n;
        column += n;
    }
    
    void Lexer::nextLine() {
        line++;
        column = 1;
    }
    
    bool Lexer::test(std::string st) {
        return st == src.substr(pos, st.size());
    }

    
} // karl