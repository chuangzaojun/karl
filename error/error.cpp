
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
                {TokenType::EndOfFile,     "end of file"},
                {TokenType::Identifier,    "identifier"},
                {TokenType::LParen,        "("},
                {TokenType::RParen,        ")"},
                {TokenType::LBracket,      "["},
                {TokenType::RBracket,      "]"},
                {TokenType::LBrace,        "{"},
                {TokenType::RBrace,        "}"},
                {TokenType::Comma,         ","},
                {TokenType::Semicolon,     ";"},
                {TokenType::Colon,         ":"},
                {TokenType::Assign,        "="},
                {TokenType::Minus,         "-"},
                {TokenType::Add,           "+"},
                {TokenType::Mul,           "/"},
                {TokenType::Mod,           "%"},
                {TokenType::LessThan,      "<"},
                {TokenType::LessEqual,     "<="},
                {TokenType::GreaterThan,   ">"},
                {TokenType::GreaterEqual,  ">="},
                {TokenType::Equal,         "=="},
                {TokenType::NotEqual,      "!="},
                {TokenType::And,           "&&"},
                {TokenType::Or,            "||"},
                {TokenType::Not,           "!"},
                {TokenType::BAnd,          "&"},
                {TokenType::BOr,           "|"},
                {TokenType::BNot,          "~"},
                {TokenType::BXor,          "^"},
                {TokenType::LMove,         "<<"},
                {TokenType::RMove,         ">>"},
                {TokenType::True,          "true"},
                {TokenType::False,         "false"},
                {TokenType::Var,           "var"},
                {TokenType::Func,          "func"},
                {TokenType::If,            "if"},
                {TokenType::Elif,          "elif"},
                {TokenType::Else,          "else"},
                {TokenType::While,         "while"},
                {TokenType::Break,         "break"},
                {TokenType::Continue,      "continue"},
                {TokenType::Return,        "return"},
                {TokenType::Int,           "int"},
                {TokenType::Bool,          "bool"},
                {TokenType::String,        "string"},
                {TokenType::Char,          "char"},
                {TokenType::Void,          "void"},
                {TokenType::IntLiteral,    "int literal"},
                {TokenType::StringLiteral, "string literal"},
                {TokenType::CharLiteral,   "char literal"}
        };
        printf("Unmatched token at line %d, column %d, expect %s.\n", readToken->line, readToken->column, typeName[expectType].data());
        exit(0);
    }

    void grammarError(Token *readToken) {
        printf("Unmatched token at line %d, column %d", readToken->line, readToken->column);
        exit(0);
    }

    void varNotFoundError(std::string var, int line, int column) {
        printf("Cannot find the variable %s at line %d, column %d.\n", var.data(), line, column);
        exit(0);
    }

    void varHasDefError(std::string var, int line, int column) {
        printf("There has been a variable %s at line %d, column %d.\n", var.data(), line, column);
        exit(0);
    }

    void funcNotFoundError(std::string func, int line, int column) {
        printf("Cannot find the function %s at line %d, column %d.\n", func.data(), line, column);
        exit(0);
    }

    void funcHasDefError(std::string func, int line, int column) {
        printf("There has been a function %s at line %d, column %d.\n", func.data(), line, column);
        exit(0);
    }

    void TypeError::invalidStmt(int line, int column) {
        printf("Invalid statement at line %d, column %d.\n", line, column);
        exit(0);
    }

    void TypeError::typeNotMatch(ObjectType *expectType, ObjectType *readType, int line, int column) {
        printf("Cannot match type at line %d, column %d, read %s, but expect %s.\n", line, column, readType->toString().data(), expectType->toString().data());
        exit(0);
    }

    void TypeError::typeNotAllowed(ObjectType *type, int line, int column) {
        printf("Type %s is not allowed at line %d, column %d.\n", type->toString().data(), line, column);
        exit(0);
    }

    void TypeError::funcCallArgumentsNumNotMatch(int expectNum, int readNum, int line, int column) {
        printf("Cannot match the number of arguments in function call expression at line %d, column %d, read %d arguments expect %d arguments.\n", line, column, readNum, expectNum);
    }
} // karl