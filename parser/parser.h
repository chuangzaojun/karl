#ifndef KARL_PARSER_H
#define KARL_PARSER_H

#include "../lexer/lexer.h"
#include "../ast/program.h"
#include <vector>

class Parser {
private:
    Lexer *lexer;
    Token *curToken;
    Token *nextToken;

    void advance();

    Stmt *parseStmt();

    Stmt *parseNullStmt();

    Stmt *parseAssStmt();

    Stmt *parseIfStmt();

    Stmt *parseWhileStmt();

    Stmt *parseExprStmt();

    Block *parseBlock();

    Expr *parseExpr();

    void expect(TokenType type);

    void error();

    Expr *parseExpr0();

    Expr *parseExpr1();

    Expr *parseExpr2();

    Expr *parseExpr3();

    Expr *parseExpr4();

    Expr *parseIntExpr();

    Expr *parseBoolExpr();

    Expr *parseVarExpr();

    Expr *parseParenExpr();

public:
    Parser(Lexer *_lexer);

    ~Parser();

    Program *parseProgram();
};

#endif // KARL_PARSER_H
