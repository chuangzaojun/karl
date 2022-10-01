#ifndef KARL_STMT_H
#define KARL_STMT_H

#include "expr.h"
#include <vector>

enum StmtType {
    STMT,
    STMT_NULL,
    STMT_ASS,
    STMT_IF,
    STMT_WHILE,
    STMT_EXPR
};

struct Stmt {
    virtual StmtType type();

    int line;
};

struct Block {
    int beginLine;
    int endLine;
    std::vector<Stmt *> stmts;
};

struct NullStmt : public Stmt {
    StmtType type() override;
};

struct AssStmt : public Stmt {
    StmtType type() override;

    Expr *variable;
    Expr *value;
};

struct IfStmt : public Stmt {
    StmtType type() override;

    Expr *condition;
    Block *ifBlock;
    Block *elseBlock;
};

struct WhileStmt : public Stmt {
    StmtType type() override;

    Expr *condition;
    Block *block;
};

struct ExprStmt : public Stmt {
    StmtType type() override;

    Expr *expr;
};

#endif // KARL_STMT_H
