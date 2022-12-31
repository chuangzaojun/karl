#include "type_checker.hpp"
#include "../../error/error.hpp"
#include <set>

namespace karl {
    TypeChecker::TypeChecker(Program *program) {
        this->program = program;
        this->curBlock = nullptr;
        this->curLoopBlock = nullptr;
    }

    void TypeChecker::checkProgram() {
        program->varTable = new VarTable(nullptr);
        program->funcTable = new FuncTable();
        for (Stmt *stmt: program->stmts) {
            switch (stmt->stmtType()) {
                case StmtType::FuncDef:
                    checkFuncDef((FuncDefStmt *) stmt);
                    break;
                case StmtType::VarDef:
                    checkGlobalVarDef((VarDefStmt *) stmt);
                    break;
                default:
                    TypeError::invalidStmt(stmt->line, stmt->column);
                    break;
            }
        }
    }

    void TypeChecker::checkGlobalVarDef(VarDefStmt *stmt) {
        for (int i = 0; i < stmt->vars.size(); i++) {
            checkType(stmt->types[i], stmt->vars[i]->line, stmt->vars[i]->column);
            if (stmt->types[i]->singleObjectType() == SingleObjectType::Void) {
                TypeError::typeNotAllowed(stmt->types[i], stmt->vars[i]->line, stmt->vars[i]->column);
            }
            if (stmt->initValues[i] != nullptr) {
                checkExpr(stmt->initValues[i], program->varTable);
                if (!stmt->types[i]->isEqual(stmt->initValues[i]->objectType)) {
                    TypeError::typeNotMatch(stmt->types[i], stmt->initValues[i]->objectType, stmt->initValues[i]->line, stmt->initValues[i]->column);
                }
            }
            program->varTable->set(((IdentifierExpr *) stmt->vars[i])->identifier, stmt->types[i], stmt->vars[i]->line, stmt->vars[i]->column);
        }
    }

    void TypeChecker::checkFuncDef(FuncDefStmt *stmt) {
        program->funcTable->set(((IdentifierExpr *) stmt->name)->identifier, stmt, stmt->line, stmt->column);
        VarTable *funcVarTable = new VarTable(program->varTable);
        for (int i = 0; i < stmt->parameters.size(); i++) {
            checkType(stmt->parameterTypes[i], stmt->parameters[i]->line, stmt->parameters[i]->column);
            if (stmt->parameterTypes[i]->singleObjectType() == SingleObjectType::Void) {
                TypeError::typeNotAllowed(stmt->parameterTypes[i], stmt->parameters[i]->line, stmt->parameters[i]->column);
            }
            funcVarTable->set(((IdentifierExpr *) stmt->parameters[i])->identifier, stmt->parameterTypes[i], stmt->parameters[i]->line, stmt->parameters[i]->column);
        }
        returnValueType = stmt->objectType;
        curBlock = stmt->block;
        returnValueType = stmt->objectType;
        checkBlock(funcVarTable);
        curBlock = nullptr;
    }

    void TypeChecker::checkBlock(VarTable *varTable) {
        curBlock->varTable = varTable;
        for (Stmt *stmt: curBlock->stmts) {
            checkStmt(stmt);
        }
    }

    void TypeChecker::checkStmt(Stmt *stmt) {
        switch (stmt->stmtType()) {
            case StmtType::FuncDef:
                TypeError::invalidStmt(stmt->line, stmt->column);
                break;
            case StmtType::VarDef:
                checkLocalVarDefStmt((VarDefStmt *) stmt);
                break;
            case StmtType::If:
                checkIfStmt((IfStmt *) stmt);
                break;
            case StmtType::While:
                checkWhileStmt((WhileStmt *) stmt);
                break;
            case StmtType::Expr:
                checkExprStmt((ExprStmt *) stmt);
                break;
            case StmtType::Break:
                checkBreakStmt((BreakStmt *) stmt);
                break;
            case StmtType::Continue:
                checkContinueStmt((ContinueStmt *) stmt);
                break;
            case StmtType::Return:
                checkReturnStmt((ReturnStmt *) stmt);
                break;
            case StmtType::Block:
                Block *temp = curBlock;
                curBlock = (Block *) stmt;
                checkBlock(new VarTable(temp->varTable));
                curBlock = temp;
                break;
        }
    }

    void TypeChecker::checkExpr(Expr *expr, VarTable *varTable) {
        switch (expr->exprType()) {
            case ExprType::Binary:
                checkBinaryExpr((BinaryExpr *) expr, varTable);
                break;
            case ExprType::Prefix:
                checkPrefixExpr((PrefixExpr *) expr, varTable);
                break;
            case ExprType::Assign:
                checkAssignExpr((AssignExpr *) expr, varTable);
                break;
            case ExprType::TypeConversion:
                checkTypeConversionExpr((TypeConversionExpr *) expr, varTable);
                break;
            case ExprType::Int:
                checkIntExpr((IntExpr *) expr, varTable);
                break;
            case ExprType::Char:
                checkCharExpr((CharExpr *) expr, varTable);
                break;
            case ExprType::String:
                checkStringExpr((StringExpr *) expr, varTable);
                break;
            case ExprType::Bool:
                checkBoolExpr((BoolExpr *) expr, varTable);
                break;
            case ExprType::FuncCall:
                checkFuncCallExpr((FuncCallExpr *) expr, varTable);
                break;
            case ExprType::ArrayIndex:
                checkArrayIndexExpr((ArrayIndexExpr *) expr, varTable);
                break;
            case ExprType::ArrayLiteral:
                checkArrayLiteralExpr((ArrayLiteralExpr *) expr, varTable);
                break;
            case ExprType::Identifier:
                checkIdentifierExpr((IdentifierExpr *) expr, varTable);
                break;
        }
    }

    void TypeChecker::checkArrayLiteralExpr(ArrayLiteralExpr *expr, VarTable *varTable) {
        for (int i = 0; i < expr->exprs.size(); i++) {
            checkExpr(expr->exprs[i], varTable);
            if (!expr->exprs[i]->objectType->isEqual(expr->exprs[0]->objectType)) {
                TypeError::typeNotMatch(expr->exprs[0]->objectType, expr->exprs[i]->objectType, expr->exprs[i]->line, expr->exprs[i]->column);
            }
        }
        expr->objectType = new ArrayObject(expr->exprs[0]->objectType->copy(), expr->exprs.size());
    }

    void TypeChecker::checkIntExpr(IntExpr *expr, VarTable *varTable) {
        expr->objectType = new IntObject();
    }

    void TypeChecker::checkCharExpr(CharExpr *expr, VarTable *varTable) {
        expr->objectType = new CharObject();
    }

    void TypeChecker::checkStringExpr(StringExpr *expr, VarTable *varTable) {
        expr->objectType = new StringObject();
    }

    void TypeChecker::checkArrayIndexExpr(ArrayIndexExpr *expr, VarTable *varTable) {
        checkIdentifierExpr((IdentifierExpr *) expr->array, varTable);
        checkExpr(expr->index, varTable);
        if (expr->index->objectType->singleObjectType() != SingleObjectType::Int) {
            TypeError::typeNotMatch(new IntObject(), expr->index->objectType, expr->index->line, expr->index->column);
        }
        if (expr->array->objectType->singleObjectType() == SingleObjectType::Char) {
            expr->objectType = new CharObject();
        } else {
            if (expr->array->objectType->singleObjectType() != SingleObjectType::Array) {
                TypeError::typeNotAllowed(expr->array->objectType, expr->array->line, expr->array->column);
            }
            expr->objectType = ((ArrayObject *) expr->array)->memberType->copy();
        }
    }

    void TypeChecker::checkBoolExpr(BoolExpr *expr, VarTable *varTable) {
        expr->objectType = new BoolObject();
    }

    void TypeChecker::checkIdentifierExpr(IdentifierExpr *expr, VarTable *varTable) {
        expr->objectType = varTable->get(expr->identifier, expr->line, expr->column)->copy();
    }

    void TypeChecker::checkTypeConversionExpr(TypeConversionExpr *expr, VarTable *varTable) {
        checkExpr(expr->expr, varTable);
        if (expr->expr->objectType->singleObjectType() == SingleObjectType::Array) {
            TypeError::typeNotAllowed(expr->expr->objectType, expr->expr->line, expr->expr->column);
        }
        if (expr->targetType == SingleObjectType::Char && expr->expr->objectType->singleObjectType() == SingleObjectType::Bool) {
            TypeError::typeNotAllowed(expr->expr->objectType, expr->expr->line, expr->expr->column);
        }
        if (expr->targetType == SingleObjectType::Bool && expr->expr->objectType->singleObjectType() == SingleObjectType::Char) {
            TypeError::typeNotAllowed(expr->expr->objectType, expr->expr->line, expr->expr->column);
        }
        if (expr->targetType == SingleObjectType::String && expr->expr->objectType->singleObjectType() == SingleObjectType::Char) {
            TypeError::typeNotAllowed(expr->expr->objectType, expr->expr->line, expr->expr->column);
        }
        if (expr->targetType == SingleObjectType::Void) {
            TypeError::typeNotAllowed(new VoidObject(), expr->line, expr->column);
        }
        switch (expr->targetType) {
            case SingleObjectType::Int:
                expr->objectType = new IntObject();
                break;
            case SingleObjectType::Char:
                expr->objectType = new CharObject();
                break;
            case SingleObjectType::Bool:
                expr->objectType = new BoolObject();
                break;
            case SingleObjectType::String:
                expr->objectType = new StringObject();
                break;
        }
    }

    void TypeChecker::checkFuncCallExpr(FuncCallExpr *expr, VarTable *varTable) {
        if (((IdentifierExpr *) expr->name)->identifier == "print") {
            for (int i = 0; i < expr->arguments.size(); i++) {
                checkExpr(expr->arguments[i], varTable);
            }
            expr->objectType = new VoidObject();
        } else {
            FuncDefStmt *func = program->funcTable->get(((IdentifierExpr *) expr->name)->identifier, expr->line,
                                                        expr->column);
            if (expr->arguments.size() != func->parameters.size()) {
                TypeError::funcCallArgumentsNumNotMatch(func->parameters.size(), expr->arguments.size(), expr->line,
                                                        expr->column);
            }
            for (int i = 0; i < expr->arguments.size(); i++) {
                checkExpr(expr->arguments[i], varTable);
                if (!expr->arguments[i]->objectType->isEqual(func->parameterTypes[i])) {
                    TypeError::typeNotMatch(func->parameterTypes[i], expr->arguments[i]->objectType,
                                            expr->arguments[i]->line, expr->arguments[i]->column);
                }
            }
            expr->objectType = func->objectType->copy();
        }
    }

    void TypeChecker::checkType(ObjectType *type, int line, int column) {
        if (type->singleObjectType() == SingleObjectType::Array) {
            checkType(((ArrayObject *) type)->memberType, line, column);
            if (((ArrayObject *) type)->memberType->singleObjectType() == SingleObjectType::Void) {
                TypeError::typeNotAllowed(((ArrayObject *) type)->memberType, line, column);
            }
        }
    }

    void TypeChecker::checkLocalVarDefStmt(VarDefStmt *stmt) {
        for (int i = 0; i < stmt->vars.size(); i++) {
            checkType(stmt->types[i], stmt->vars[i]->line, stmt->vars[i]->column);
            if (stmt->types[i]->singleObjectType() == SingleObjectType::Void) {
                TypeError::typeNotAllowed(stmt->types[i], stmt->vars[i]->line, stmt->vars[i]->column);
            }
            if (stmt->initValues[i] != nullptr) {
                checkExpr(stmt->initValues[i], curBlock->varTable);
                if (!stmt->types[i]->isEqual(stmt->initValues[i]->objectType)) {
                    TypeError::typeNotMatch(stmt->types[i], stmt->initValues[i]->objectType, stmt->initValues[i]->line, stmt->initValues[i]->column);
                }
            }
            curBlock->varTable->set(((IdentifierExpr *) stmt->vars[i])->identifier, stmt->types[i], stmt->vars[i]->line, stmt->vars[i]->column);
        }
    }

    void TypeChecker::checkIfStmt(IfStmt *stmt) {
        for (int i = 0; i < stmt->conditions.size(); i++) {
            checkExpr(stmt->conditions[i], curBlock->varTable);
            if (stmt->conditions[i]->objectType->singleObjectType() != SingleObjectType::Bool) {
                TypeError::typeNotMatch(new BoolObject(), stmt->conditions[i]->objectType, stmt->conditions[i]->line, stmt->conditions[i]->column);
            }
            Block *temp = curBlock;
            curBlock = stmt->blocks[i];
            checkBlock(new VarTable(temp->varTable));
            curBlock = temp;
        }
        if (stmt->blocks.size() > stmt->conditions.size()) {
            Block *temp = curBlock;
            curBlock = stmt->blocks[stmt->blocks.size() - 1];
            checkBlock(new VarTable(temp->varTable));
            curBlock = temp;
        }
    }

    void TypeChecker::checkWhileStmt(WhileStmt *stmt) {
        checkExpr(stmt->condition, curBlock->varTable);
        Block *temp = curBlock;
        Block *loopTemp = curLoopBlock;
        curBlock = curLoopBlock = stmt->block;
        checkBlock(new VarTable(temp->varTable));
        curBlock = temp;
        curLoopBlock = loopTemp;
    }

    void TypeChecker::checkExprStmt(ExprStmt *stmt) {
        checkExpr(stmt->expr, curBlock->varTable);
    }

    void TypeChecker::checkReturnStmt(ReturnStmt *stmt) {
        if (stmt->expr == nullptr) {
            if (returnValueType->singleObjectType() != SingleObjectType::Void) {
                TypeError::typeNotMatch(returnValueType, new VoidObject(), stmt->line, stmt->column);
            }
        } else {
            checkExpr(stmt->expr, curBlock->varTable);
            if (!returnValueType->isEqual(stmt->expr->objectType)) {
                TypeError::typeNotMatch(returnValueType, stmt->expr->objectType, stmt->line, stmt->column);
            }
        }
    }

    void TypeChecker::checkAssignExpr(AssignExpr *expr, VarTable *varTable) {
        checkExpr(expr->left, varTable);
        checkExpr(expr->right, varTable);
        if (!expr->left->objectType->isEqual(expr->right->objectType)) {
            TypeError::typeNotMatch(expr->left->objectType, expr->right->objectType, expr->line, expr->column);
        }
        if (expr->left->exprType() != ExprType::Identifier && expr->left->exprType() != ExprType::ArrayIndex) {
            TypeError::invalidOp(OpType::Assign, expr->line, expr->column);
        }
        expr->objectType = expr->left->objectType->copy();
    }

    void TypeChecker::checkBreakStmt(BreakStmt *stmt) {
        if (curLoopBlock == nullptr) {
            TypeError::invalidStmt(stmt->line, stmt->column);
        }
        stmt->loopBlock = curLoopBlock;
        curLoopBlock->breakStmts.push_back(stmt);
    }

    void TypeChecker::checkContinueStmt(ContinueStmt *stmt) {
        if (curLoopBlock == nullptr) {
            TypeError::invalidStmt(stmt->line, stmt->column);
        }
        stmt->loopBlock = curLoopBlock;
        curLoopBlock->continueStmts.push_back(stmt);
    }

    void TypeChecker::checkPrefixExpr(PrefixExpr *expr, VarTable *varTable) {
        checkExpr(expr->right, varTable);
        if (expr->right->objectType->singleObjectType() != SingleObjectType::Int) {
            TypeError::invalidOp(expr->op, expr->line, expr->column);
        }
        expr->objectType = new IntObject();
    }

    void TypeChecker::checkBinaryExpr(BinaryExpr *expr, VarTable *varTable) {
        checkExpr(expr->left, varTable);
        checkExpr(expr->right, varTable);
        if (expr->op == OpType::Add) {
            if (expr->left->objectType->singleObjectType() == SingleObjectType::String || expr->left->objectType->singleObjectType() == SingleObjectType::Char) {
                if (expr->right->objectType->singleObjectType() == SingleObjectType::String || expr->right->objectType->singleObjectType() == SingleObjectType::Char) {
                    expr->objectType = new StringObject();
                    return;
                }
            }
        }
        if (!expr->left->objectType->isEqual(expr->right->objectType) || expr->left->objectType->singleObjectType() == SingleObjectType::Array) {
            TypeError::invalidOp(expr->op, expr->line, expr->column);
        }
        switch (expr->op) {
            case OpType::Add:
            case OpType::Minus:
            case OpType::Mul:
            case OpType::Div:
            case OpType::Mod:
            case OpType::BAnd:
            case OpType::BOr:
            case OpType::BXor:
            case OpType::LMove:
            case OpType::RMove:
                if (expr->left->objectType->singleObjectType() != SingleObjectType::Int) {
                    TypeError::invalidOp(expr->op, expr->line, expr->column);
                }
                expr->objectType = new IntObject();
                break;
            case OpType::LessThan:
            case OpType::LessEqual:
            case OpType::GreaterThan:
            case OpType::GreaterEqual:
                if (expr->left->objectType->singleObjectType() != SingleObjectType::Int && expr->left->objectType->singleObjectType() != SingleObjectType::Char) {
                    TypeError::invalidOp(expr->op, expr->line, expr->column);
                }
                expr->objectType = new BoolObject();
                break;
            case OpType::Equal:
            case OpType::NotEqual:
                expr->objectType = new BoolObject();
                break;
            case OpType::And:
            case OpType::Or:
                if (expr->left->objectType->singleObjectType() != SingleObjectType::Bool) {
                    TypeError::invalidOp(expr->op, expr->line, expr->column);
                }
                expr->objectType = new BoolObject();
                break;
        }
    }


} // karl