#include "evaluator.h"

void Evaluator::evalProgram(Program *program) {
    for (std::vector<Stmt *>::iterator it = program->stmts.begin(); it != program->stmts.end(); it++) {
        evalStmt(*it);
    }
}

void Evaluator::evalBlock(Block *block) {
    for (std::vector<Stmt *>::iterator it = block->stmts.begin(); it != block->stmts.end(); it++) {
        evalStmt(*it);
    }
}

void Evaluator::evalStmt(Stmt *stmt) {
    switch (stmt->type()) {
        case STMT_ASS:
            evalAssStmt((AssStmt *) stmt);
            break;
        case STMT_IF:
            evalIfStmt((IfStmt *) stmt);
            break;
        case STMT_WHILE:
            evalWhileStmt((WhileStmt *) stmt);
            break;
        case STMT_EXPR:
            evalExprStmt((ExprStmt *) stmt);
            break;
    }
}

Object *Evaluator::evalExpr(Expr *expr) {
    switch (expr->type()) {
        case EXPR_PREFIX:
            return evalPrefixExpr((PrefixExpr *) expr);
        case EXPR_BINARY:
            return evalBinaryExpr((BinaryExpr *) expr);
        case EXPR_INT:
            return evalIntExpr((IntExpr *) expr);
        case EXPR_BOOL:
            return evalBoolExpr((BoolExpr *) expr);
        case EXPR_VAR:
            return evalVarExpr((VarExpr *) expr);
    }
    return NULL;
}

Object *Evaluator::evalPrefixExpr(PrefixExpr *expr) {
    switch (expr->op) {
        case OP_NOT:
            return no(evalExpr(expr->right));
        case OP_MINUS:
            return minus(evalExpr(expr->right));
    }
    return NULL;
}

Object *Evaluator::evalBinaryExpr(BinaryExpr *expr) {
    switch (expr->op) {
        case OP_MINUS:
            return minus(evalExpr(expr->left), evalExpr(expr->right));
        case OP_ADD:
            return add(evalExpr(expr->left), evalExpr(expr->right));
        case OP_MUL:
            return mul(evalExpr(expr->left), evalExpr(expr->right));
        case OP_DIV:
            return div(evalExpr(expr->left), evalExpr(expr->right));
        case OP_MOD:
            return mod(evalExpr(expr->left), evalExpr(expr->right));
        case OP_LT:
            return lt(evalExpr(expr->left), evalExpr(expr->right));
        case OP_LE:
            return le(evalExpr(expr->left), evalExpr(expr->right));
        case OP_GT:
            return gt(evalExpr(expr->left), evalExpr(expr->right));
        case OP_GE:
            return ge(evalExpr(expr->left), evalExpr(expr->right));
        case OP_EQ:
            return eq(evalExpr(expr->left), evalExpr(expr->right));
        case OP_NE:
            return ne(evalExpr(expr->left), evalExpr(expr->right));
    }
    return NULL;
}

Object *Evaluator::evalIntExpr(IntExpr *expr) {
    IntObject *object = new IntObject{};
    object->value = expr->value;
    return object;
}

Object *Evaluator::evalBoolExpr(BoolExpr *expr) {
    BoolObject *object = new BoolObject{};
    object->value = expr->value;
    return object;
}

Object *Evaluator::evalVarExpr(VarExpr *expr) {
    return copy(environment->get(expr->identifier));
}

void Evaluator::evalAssStmt(AssStmt *stmt) {
    environment->set(((VarExpr *) stmt->variable)->identifier, evalExpr(stmt->value));
}

void Evaluator::evalIfStmt(IfStmt *stmt) {
    if (getBoolValue(evalExpr(stmt->condition))) {
        evalBlock(stmt->ifBlock);
    } else {
        if (stmt->elseBlock != NULL) {
            evalBlock(stmt->elseBlock);
        }
    }
}

void Evaluator::evalWhileStmt(WhileStmt *stmt) {
    while (getBoolValue(evalExpr(stmt->condition))) {
        evalBlock(stmt->block);
    }
}

void Evaluator::evalExprStmt(ExprStmt *stmt) {
    Object *object = evalExpr(stmt->expr);
    if (object->type() == OBJECT_INT) {
        printf("%d\n", getIntValue(object));
    } else {
        if (getBoolValue(object)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
    }
    delete object;
}

Evaluator::Evaluator(Environment *_environment) {
    environment = _environment;
}