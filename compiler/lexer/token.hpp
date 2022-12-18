#ifndef KARL_TOKEN_HPP
#define KARL_TOKEN_HPP

#include <string>

namespace karl {

    enum class TokenType {
        _,

        EndOfFile,

        Identifier,

        LParen, // (
        RParen, // )
        LBracket, // [
        RBracket, // ]
        LBrace, // {
        RBrace, // }

        Comma, // ,
        Semicolon, // ;
        Colon, // :

        Assign, // =
        Minus, // -
        Add, // +
        Mul, // *
        Div, // /
        Mod, // %
        LessThan, // <
        LessEqual, // <=
        GreaterThan, // >
        GreaterEqual, // >=
        Equal, // ==
        NotEqual, // !=

        And, // &&
        Or, // ||
        Not, // !

        BAnd, // &
        BOr, // |
        BNot, // ~
        BXor, // ^
        LMove, // <<
        RMove, // >>

        // keywords
        True,
        False,
        Var,
        Func,
        If,
        Elif,
        Else,
        While,
        Break,
        Continue,
        Return,

        // type
        Int,
        Bool,
        String,
        Char,
        Void,

        // literals
        IntLiteral,
        StringLiteral,
        CharLiteral
    };

    struct Token {
        TokenType type;
        std::string literal;
        int line;
        int column;

        Token(TokenType _type, std::string _literal, int _line, int _column);
    };

} // karl

#endif // KARL_TOKEN_HPP
