#include "expr.h"

ExprType Expr::type() {
    return EXPR;
}

ExprType IntExpr::type() {
    return EXPR_INT;
}

ExprType BoolExpr::type() {
    return EXPR_BOOL;
}

ExprType PrefixExpr::type() {
    return EXPR_PREFIX;
}

ExprType BinaryExpr::type() {
    return EXPR_BINARY;
}

ExprType VarExpr::type() {
    return EXPR_VAR;
}