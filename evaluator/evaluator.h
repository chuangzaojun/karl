#ifndef KARL_EVALUATOR_H
#define KARL_EVALUATOR_H

#include "environment.h"
#include "../ast/program.h"

class Evaluator {
private:
    Environment *environment;

    void evalStmt(Stmt *stmt);

    void evalAssStmt(AssStmt *stmt);

    void evalIfStmt(IfStmt *stmt);

    void evalWhileStmt(WhileStmt *stmt);

    void evalExprStmt(ExprStmt *stmt);

    void evalBlock(Block *block);

    Object *evalExpr(Expr *expr);

    Object *evalPrefixExpr(PrefixExpr *expr);

    Object *evalBinaryExpr(BinaryExpr *expr);

    Object *evalIntExpr(IntExpr *expr);

    Object *evalBoolExpr(BoolExpr *expr);

    Object *evalVarExpr(VarExpr *expr);

public:
    void evalProgram(Program *program);

    Evaluator(Environment *_environment);
};


#endif // KARL_EVALUATOR_H
