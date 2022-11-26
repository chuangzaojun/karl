#include "lexer.hpp"

namespace karl {

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
        pos = 0;
    }

    void Lexer::next(int n) {
        pos += n;
    }

    bool Lexer::test(std::string st) {
        return st == src.substr(pos, st.size());
    }

    void Lexer::skipComment() {

    }
} // karl