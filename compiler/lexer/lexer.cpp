#include "lexer.hpp"
#include <map>
#include <string>

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

    void Lexer::skipWhiteSpace() {
        while (true) {
            if (isWhiteSpace(src[pos])) {
                next(1);
            } else if (test("\r\n") || test("\n\r")) {
                next(2);
                nextLine();
            } else if (isNewLine(src[pos])) {
                next(1);
                nextLine();
            } else if (test("//") || test("/*")) {
                skipComment();
            } else {
                break;
            }
        }
    }

    bool Lexer::skipComment() {
        if (test("//")) {
            while (!isNewLine(src[pos])) {
                next(1);
            }
        } else {
            while (!test("*/")) {
                if (test("\r\n") || test("\n\r")) {
                    next(2);
                    nextLine();
                } else if (isNewLine(src[pos])) {
                    next(1);
                    nextLine();
                } else {
                    next(1);
                }
            }
            next(2);
        }
    }
    
    Token *Lexer::newToken(TokenType type, std::string literal) {
        return new Token(type, literal, line, column);
    }

    Token *Lexer::newToken(TokenType type) {
        return new Token(type, "", line, column);
    }

    std::string Lexer::scanIdentifier() {
        std::string iden;
        while(isLetter(src[pos]) || isDigit(src[pos]) || src[pos] == '_') {
            iden += src[pos];
            next(1);
        }
        return iden;
    }

    std::string scanInt() {
        std::string intNum;
        while (isDigit(src[pos])) {
            intNum += src[pos];
            next(1);
        }
        return intNum;
    }

    Token *Lexer::nextToken() {
        skipWhiteSpace();
        switch (src[pos]) {
        case '(':
            next(1);
            return newToken(TokenType::LParen);
        case ')':
            next(1);
            return newToken(TokenType::RParen);
        case '[':
            next(1);
            return newToken(TokenType::LBracket);
        case ']':
            next(1);
            return newToken(TokenType::RBracket);
        case '{':
            next(1);
            return newToken(TokenType::LBrace);
        case '}':
            next(1);
            return newToken(TokenType::RBrace);
        case ',':
            next(1);
            return newToken(TokenType::Comma);
        case ';':
            next(1);
            return newToken(TokenType::Semicolon);
        case ':':
            return newToken(TokenType::Colon);
        case '=':
            if (test("==")) {
                next(2);
                return newToken(TokenType::Equal);
            }
            return newToken(TokenType::Assign);
        case '<':
            if (test("<<")) {
                next(2);
                return newToken(TokenType::LMove);
            }
            if (test("<=")) {
                next(2);
                return newToken(TokenType::LessEqual);
            }
            next(1);
            return newToken(TokenType::LessThan);
        case '>':
            if (test(">>")) {
                next(2);
                return newToken(TokenType::LMove);
            }
            if (test(">=")) {
                next(2);
                return newToken(TokenType::GreaterEqual);
            }
            next(1);
            return newToken(TokenType::GreaterThan);
        case '!':
            if (test("!=")) {
                next(2);
                return newToken(TokenType::NotEqual);
            }
            next(1);
            return newToken(TokenType::Not);
        case '&':
            if (test("&&")) {
                next(2);
                return newToken(TokenType::And);
            }
            next(1);
            return newToken(TokenType::BAnd);
        case '|':
            if (test("||")) {
                next(2);
                return newToken(TokenType::Or);
            }
            next(1);
            return newToken(TokenType::BOr);
        case '~':
            next(1);
            return newToken(TokenType::BNot);
        case '^':
            next(1);
            return newToken(TokenType::BXor);
        }
        if (isLetter(src[pos]) || src[pos] == '_') {
            std::string iden = scanIdentifier();
            if (keywords.count(iden)) {
                return newToken(keywords[iden]);
            }
            return newToken(TokenType::Identifier, iden);
        }
        if (isDigit(src[pos])) {
            
            return newToken(TokenType::IntLiteral, scanInt());
        }
    }
} // karl