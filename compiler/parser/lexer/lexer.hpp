#ifndef KARL_LEXER_HPP
#define KARL_LEXER_HPP

#include "token.hpp"
#include <string>

namespace karl {
    namespace compiler {
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
            std::string scanInt();
            std::string scanString();
            std::string scanChar();
            std::string scanIdentifier();
            Token *newToken(TokenType type, std::string literal);
            Token *newToken(TokenType type);

        public:
            Lexer(std::string _src);
            Token *nextToken();
        };
    }

}

#endif // KARL_LEXER_HPP
