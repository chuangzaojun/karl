#ifndef KARL_EXPR_H
#define KARL_EXPR_H

#include <string>

enum OperatorKind {
    OP_MINUS, // -
    OP_ADD, // +
    OP_MUL, // *
    OP_DIV, // /
    OP_MOD, // %
    OP_LT, // <
    OP_LE, // <=
    OP_GT, // >
    OP_GE, // >=
    OP_EQ, // ==
    OP_NE, // !=
    OP_NOT, // !
};

enum ExprType {
    EXPR,
    EXPR_INT,
    EXPR_BOOL,
    EXPR_VAR,
    EXPR_PREFIX,
    EXPR_BINARY
};

struct Expr {
    int line;

    virtual ExprType type();
};

struct IntExpr : public Expr {
    int value;

    ExprType type() override;
};

struct BoolExpr : public Expr {
    bool value;

    ExprType type() override;
};

struct VarExpr : public Expr {
    std::string identifier;

    ExprType type() override;
};

struct PrefixExpr : public Expr {
    OperatorKind op;
    Expr *right;

    ExprType type() override;
};

struct BinaryExpr : public Expr {
    OperatorKind op;
    Expr *left;
    Expr *right;

    ExprType type() override;
};

#endif // KARL_EXPR_H
