#include "parser.h"

Parser::Parser(Lexer *_lexer) {
    lexer = _lexer;
    curToken = nextToken = NULL;
    advance();
    advance();
}

Parser::~Parser() {
    delete lexer;
    delete curToken;
    delete nextToken;
}

void Parser::advance() {
    if (curToken != NULL) {
        delete curToken;
    }
    curToken = nextToken;
    nextToken = lexer->nextToken();
}

Program *Parser::parseProgram() {
    Program *program = new Program{};
    while (curToken->getType() != TOKEN_EOF) {
        program->stmts.push_back(parseStmt());
    }
    return program;
}

Stmt *Parser::parseStmt() {
    switch (curToken->getType()) {
        case TOKEN_SEP_SEMI:
            return parseNullStmt();
        case TOKEN_KW_IF:
            return parseIfStmt();
        case TOKEN_KW_WHILE:
            return parseWhileStmt();
    }
    if (curToken->getType() == TOKEN_IDENTIFIER) {
        if (nextToken->getType() == TOKEN_OP_ASSIGN) {
            return parseAssStmt();
        }
    }
    return parseExprStmt();
}

Block *Parser::parseBlock() {
    Block *block = new Block{};
    block->beginLine = curToken->getLine();
    expect(TOKEN_SEP_LCURLY);
    while (curToken->getType() != TOKEN_SEP_RCURLY) {
        block->stmts.push_back(parseStmt());
    }
    block->endLine = curToken->getLine();
    expect(TOKEN_SEP_RCURLY);
    return block;
}

Stmt *Parser::parseIfStmt() {
    IfStmt *stmt = new IfStmt{};
    stmt->line = curToken->getLine();
    advance();
    stmt->condition = parseExpr();
    stmt->ifBlock = parseBlock();
    if (curToken->getType() == TOKEN_KW_ELSE) {
        advance();
        stmt->elseBlock = parseBlock();
    }
    return stmt;
}

Stmt *Parser::parseWhileStmt() {
    WhileStmt *stmt = new WhileStmt{};
    stmt->line = curToken->getLine();
    advance();
    stmt->condition = parseExpr();
    stmt->block = parseBlock();
    return stmt;
}

Stmt *Parser::parseExprStmt() {
    ExprStmt *stmt = new ExprStmt{};
    stmt->line = curToken->getLine();
    stmt->expr = parseExpr();
    expect(TOKEN_SEP_SEMI);
    return stmt;
}

Stmt *Parser::parseAssStmt() {
    AssStmt *stmt = new AssStmt{};
    stmt->line = curToken->getLine();
    stmt->variable = parseExpr();
    expect(TOKEN_OP_ASSIGN);
    stmt->value = parseExpr();
    expect(TOKEN_SEP_SEMI);
    return stmt;
}

Stmt *Parser::parseNullStmt() {
    NullStmt *stmt = new NullStmt{};
    stmt->line = curToken->getLine();
    expect(TOKEN_SEP_SEMI);
    return stmt;
}

void Parser::expect(TokenType type) {
    if (curToken->getType() == type) {
        advance();
    } else {
        error();
    }
}

void Parser::error() {
    printf("unmatched token at line %d\n", curToken->getLine());
    exit(0);
}

Expr *Parser::parseExpr() {
    return parseExpr4();
}

Expr *Parser::parseExpr4() {
    Expr *expr = parseExpr3();
    while (true) {
        if (curToken->getType() == TOKEN_OP_LT) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_LT;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_LT);
            ((BinaryExpr *) expr)->right = parseExpr3();
        } else if (curToken->getType() == TOKEN_OP_LE) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_LE;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_LE);
            ((BinaryExpr *) expr)->right = parseExpr3();
        } else if (curToken->getType() == TOKEN_OP_GT) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_GT;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_GT);
            ((BinaryExpr *) expr)->right = parseExpr3();
        } else if (curToken->getType() == TOKEN_OP_GE) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_GE;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_GE);
            ((BinaryExpr *) expr)->right = parseExpr3();
        } else if (curToken->getType() == TOKEN_OP_EQ) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_EQ;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_EQ);
            ((BinaryExpr *) expr)->right = parseExpr3();
        } else if (curToken->getType() == TOKEN_OP_NE) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_NE;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_NE);
            ((BinaryExpr *) expr)->right = parseExpr3();
        } else {
            return expr;
        }
    }
    return expr;
}

Expr *Parser::parseExpr3() {
    Expr *expr = parseExpr2();
    while (true) {
        if (curToken->getType() == TOKEN_OP_ADD) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_ADD;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_ADD);
            ((BinaryExpr *) expr)->right = parseExpr2();
        } else if (curToken->getType() == TOKEN_OP_MINUS) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_MINUS;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_MINUS);
            ((BinaryExpr *) expr)->right = parseExpr2();
        } else {
            return expr;
        }
    }
    return expr;
}

Expr *Parser::parseExpr2() {
    Expr *expr = parseExpr1();
    while (true) {
        if (curToken->getType() == TOKEN_OP_MUL) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_MUL;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_MUL);
            ((BinaryExpr *) expr)->right = parseExpr1();
        } else if (curToken->getType() == TOKEN_OP_DIV) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_DIV;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_DIV);
            ((BinaryExpr *) expr)->right = parseExpr1();
        } else if (curToken->getType() == TOKEN_OP_MOD) {
            Expr *t = expr;
            expr = new BinaryExpr{};
            ((BinaryExpr *) expr)->left = t;
            ((BinaryExpr *) expr)->op = OP_MOD;
            ((BinaryExpr *) expr)->line = curToken->getLine();
            expect(TOKEN_OP_MOD);
            ((BinaryExpr *) expr)->right = parseExpr1();
        } else {
            return expr;
        }
    }
    return expr;
}

Expr *Parser::parseExpr1() {
    if (curToken->getType() == TOKEN_OP_MINUS) {
        PrefixExpr *expr = new PrefixExpr{};
        expr->op = OP_MINUS;
        expr->line = curToken->getLine();
        advance();
        expr->right = parseExpr0();
        return expr;
    } else if (curToken->getType() == TOKEN_OP_NOT) {
        PrefixExpr *expr = new PrefixExpr{};
        expr->op = OP_NOT;
        expr->line = curToken->getLine();
        advance();
        expr->right = parseExpr0();
        return expr;
    }
    return parseExpr0();
}

Expr *Parser::parseExpr0() {
    switch (curToken->getType()) {
        case TOKEN_INT:
            return parseIntExpr();
        case TOKEN_KW_TRUE:
            return parseBoolExpr();
        case TOKEN_KW_FALSE:
            return parseBoolExpr();
        case TOKEN_IDENTIFIER:
            return parseVarExpr();
        case TOKEN_SEP_LPAREN:
            return parseParenExpr();
    }
    error();
    return NULL;
}

Expr *Parser::parseIntExpr() {
    IntExpr *expr = new IntExpr{};
    expr->value = std::stoi(curToken->getValue());
    expr->line = curToken->getLine();
    advance();
    return expr;
}

Expr *Parser::parseBoolExpr() {
    BoolExpr *expr = new BoolExpr{};
    if (curToken->getType() == TOKEN_KW_TRUE) {
        expr->value = true;
    } else {
        expr->value = false;
    }
    expr->line = curToken->getLine();
    advance();
    return expr;
}

Expr *Parser::parseVarExpr() {
    VarExpr *expr = new VarExpr{};
    expr->line = curToken->getLine();
    expr->identifier = curToken->getValue();
    advance();
    return expr;
}

Expr *Parser::parseParenExpr() {
    expect(TOKEN_SEP_LPAREN);
    Expr *expr = parseExpr();
    expect(TOKEN_SEP_RPAREN);
    return expr;
}