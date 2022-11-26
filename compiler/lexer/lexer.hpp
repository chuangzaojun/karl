#ifndef KARL_LEXER_HPP
#define KARL_LEXER_HPP

#include "token.hpp"

namespace karl {

    class Lexer {
    private:
        std::string src;
        int pos;
        int line; // number of line
        int column; // number of column

        void next(int n);
        void nextLine();
        bool test(std::string st);
        void skipWhiteSpace();
        void skipComment();
        
    public:
        Lexer(std::string _src);
        Token *nextToken();
    };

} // karl

#endif // KARL_LEXER_HPP
