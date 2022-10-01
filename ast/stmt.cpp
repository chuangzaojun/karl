#include "stmt.h"

StmtType Stmt::type() {
    return STMT;
}

StmtType IfStmt::type() {
    return STMT_IF;
}

StmtType WhileStmt::type() {
    return STMT_WHILE;
}

StmtType NullStmt::type() {
    return STMT_NULL;
}

StmtType AssStmt::type() {
    return STMT_ASS;
}

StmtType ExprStmt::type() {
    return STMT_EXPR;
}