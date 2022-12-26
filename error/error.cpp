
#include "error.hpp"
#include <iostream>
#include <map>

namespace karl {
    void lexError(int line, int column) {
        printf("Unknown token at line %d, column %d.\n", line, column);
        exit(0);
    }

    void grammarError(TokenType expectType, Token *readToken) {
        std::map<TokenType, std::string> typeName = {
            {TokenType::EndOfFile, "end of file"},
            {TokenType::Identifier, "identifier"},
            {TokenType::LParen, "("},
            {TokenType::RParen, ")"},
            {TokenType::LBracket, "["},
            {TokenType::RBracket, "]"},
            {TokenType::LBrace, "{"},
            {TokenType::RBrace, "}"},
            {TokenType::Comma, ","},
            {TokenType::Semicolon, ";"},
            {TokenType::Colon, ":"},
            {TokenType::Assign, "="},
            {TokenType::Minus, "-"},
            {TokenType::Add, "+"},
            {TokenType::Mul, "/"},
            {TokenType::Mod, "%"},
            {TokenType::LessThan, "<"},
            {TokenType::LessEqual, "<="},
            {TokenType::GreaterThan, ">"},
            {TokenType::GreaterEqual, ">="},
            {TokenType::Equal, "=="},
            {TokenType::NotEqual, "!="},
            {TokenType::And, "&&"},
            {TokenType::Or, "||"},
            {TokenType::Not, "!"},
            {TokenType::BAnd, "&"},
            {TokenType::BOr, "|"},
            {TokenType::BNot, "~"},
            {TokenType::BXor, "^"},
            {TokenType::LMove, "<<"},
            {TokenType::RMove, ">>"},
            {TokenType::True, "true"},
            {TokenType::False, "false"},
            {TokenType::Var, "var"},
            {TokenType::Func, "func"},
            {TokenType::If, "if"},
            {TokenType::Elif, "elif"},
            {TokenType::Else, "else"},
            {TokenType::While, "while"},
            {TokenType::Break, "break"},
            {TokenType::Continue, "continue"},
            {TokenType::Return, "return"},
            {TokenType::Int, "int"},
            {TokenType::Bool, "bool"},
            {TokenType::String, "string"},
            {TokenType::Char, "char"},
            {TokenType::Void, "void"},
            {TokenType::IntLiteral, "int literal"},
            {TokenType::StringLiteral, "string literal"},
            {TokenType::CharLiteral, "char literal"}
        };
        printf("Unmatched token at line %d, column %d, expect %s.\n", readToken->line, readToken->column, )
        exit(0);
    }

    void grammarError(Token *readToken) {
        printf("Unmatched token at line %d, column %d", readToken->line, readToken->column);
        exit(0);
    }
} // karl