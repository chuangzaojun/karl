#include "lexer.hpp"
#include "../../error/error.hpp"
#include <map>
#include <string>

namespace karl {

    std::map<std::string, TokenType> keywords = {
            {"true",     TokenType::True},
            {"false",    TokenType::False},
            {"var",      TokenType::Var},
            {"func",     TokenType::Func},
            {"if",       TokenType::If},
            {"elif",     TokenType::Elif},
            {"else",     TokenType::Else},
            {"while",    TokenType::While},
            {"break",    TokenType::Break},
            {"continue", TokenType::Continue},
            {"return",   TokenType::Return},
            {"int",      TokenType::Int},
            {"bool",     TokenType::Bool},
            {"string",   TokenType::String},
            {"char",     TokenType::Char},
            {"void",     TokenType::Void}
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

    void Lexer::skipComment() {
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
        while (isLetter(src[pos]) || isDigit(src[pos]) || src[pos] == '_') {
            iden += src[pos];
            next(1);
        }
        return iden;
    }

    std::string Lexer::scanInt() {
        std::string intNum;
        while (isDigit(src[pos])) {
            intNum += src[pos];
            next(1);
        }
        return intNum;
    }

    Token *Lexer::nextToken() {
        skipWhiteSpace();
        if (pos == src.size()) {
            return newToken(TokenType::EndOfFile);
        }
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
                next(1);
                return newToken(TokenType::Colon);
            case '=':
                if (test("==")) {
                    next(2);
                    return newToken(TokenType::Equal);
                }
                next(1);
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
                    return newToken(TokenType::RMove);
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
            case '+':
                next(1);
                return newToken(TokenType::Add);
            case '-':
                next(1);
                return newToken(TokenType::Minus);
            case '*':
                next(1);
                return newToken(TokenType::Mul);
            case '/':
                next(1);
                return newToken(TokenType::Div);
            case '%':
                next(1);
                return newToken(TokenType::Mod);
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
        if (src[pos] == '\'') {
            return newToken(TokenType::CharLiteral, scanChar());
        }
        if (src[pos] == '\"') {
            return newToken(TokenType::StringLiteral, scanString());
        }
        lexError(line, column);
        return nullptr;
    }

    std::string Lexer::scanChar() {
        std::string ch;
        next(1);
        while (src[pos] != '\'') {
            if (src[pos] == '\\') {
                switch (src[pos + 1]) {
                    case 'a':
                        next(2);
                        ch += '\a';
                        continue;
                    case 'b':
                        next(2);
                        ch += '\b';
                        continue;
                    case 'f':
                        next(2);
                        ch += '\f';
                        continue;
                    case 'n':
                        next(2);
                        ch += '\n';
                        continue;
                    case 'r':
                        next(2);
                        ch += '\r';
                        continue;
                    case 't':
                        next(2);
                        ch += '\t';
                        continue;
                    case 'v':
                        next(2);
                        ch += '\v';
                        continue;
                    case '\"':
                        next(2);
                        ch += '\"';
                        continue;
                    case '\'':
                        next(2);
                        ch += '\'';
                        continue;
                    case '\\':
                        next(2);
                        ch += '\\';
                        continue;
                }
                ch += src[pos];
                next(1);
            } else {
                ch += src[pos];
                next(1);
                if (isNewLine(src[pos])) {
                    lexError(line, column);
                }
            }
        }
        next(1);
        if (ch.size() != 1) {
            lexError(line, column);
        }
        return ch;
    }

    std::string Lexer::scanString() {
        std::string st;
        next(1);
        while (src[pos] != '\"') {
            if (src[pos] == '\\') {
                switch (src[pos + 1]) {
                    case 'a':
                        next(2);
                        st += '\a';
                        continue;
                    case 'b':
                        next(2);
                        st += '\b';
                        continue;
                    case 'f':
                        next(2);
                        st += '\f';
                        continue;
                    case 'n':
                        next(2);
                        st += '\n';
                        continue;
                    case 'r':
                        next(2);
                        st += '\r';
                        continue;
                    case 't':
                        next(2);
                        st += '\t';
                        continue;
                    case 'v':
                        next(2);
                        st += '\v';
                        continue;
                    case '"':
                        next(2);
                        st += '\"';
                        continue;
                    case '\'':
                        next(2);
                        st += '\'';
                        continue;
                    case '\\':
                        next(2);
                        st += '\\';
                        continue;
                }
                st += src[pos];
                next(1);
            } else {
                st += src[pos];
                next(1);
                if (isNewLine(src[pos])) {
                    lexError(line, column);
                }
            }
        }
        next(1);
        return st;
    }
} // karl