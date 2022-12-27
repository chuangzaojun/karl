#ifndef KARL_PARSER_HPP
#define KARL_PARSER_HPP

#include "../lexer/lexer.hpp"
#include "../ast/program.hpp"

namespace karl {

    class Parser {
    private:
        Lexer *lexer;
        Token *curToken;
        Token *nextToken;

        void advance();
        void skip(TokenType type);
        void expect(TokenType type);

        Stmt *parseStmt();
        Stmt *parseVarDefStmt();
        Stmt *parseFuncDefStmt();
        Stmt *parseWhileStmt();
        Stmt *parseIfStmt();
        Stmt *parseBreakStmt();
        Stmt *parseContinueStmt();
        Stmt *parseReturnStmt();
        Stmt *parseExprStmt();

        Block *parseBlock();

        Expr *parseExpr();

        Expr *parseArrayLiteralExpr();

        Expr *parseExpr12();
        Expr *parseExpr11();
        Expr *parseExpr10();
        Expr *parseExpr9();
        Expr *parseExpr8();
        Expr *parseExpr7();
        Expr *parseExpr6();
        Expr *parseExpr5();
        Expr *parseExpr4();
        Expr *parseExpr3();
        Expr *parseExpr2();
        Expr *parseExpr1();
        Expr *parseExpr0();

        Expr *parseIdentifier();
        Expr *parseArrayIndexExpr();
        Expr *parseFuncCallExpr();
        Expr *parseIntExpr();
        Expr *parseBoolExpr();
        Expr *parseCharExpr();
        Expr *parseStringExpr();
        Expr *parseTypeConversionExpr();

        ObjectType *parseType();
        ObjectType *parseSingleType();

    public:
        Parser(Lexer *lexer);
        Program *parseProgram();
    };

} // karl

#endif //KARL_PARSER_HPP
