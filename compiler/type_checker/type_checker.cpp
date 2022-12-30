#include "type_checker.hpp"
#include "../../error/error.hpp"

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
                case StmtType::VarDef:
                    checkGlobalVarDef((VarDefStmt *) stmt);
                default:
                    TypeError::invalidStmt(stmt->line, stmt->column);
            }
        }
    }

    void TypeChecker::checkGlobalVarDef(VarDefStmt *stmt) {
        for (int i = 0; i < stmt->vars.size(); i++) {
            checkType(stmt->types[i]);
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
        for (int i = 0; i < stmt->parameters.size(); i++) {
            checkType(stmt->parameterTypes[i]);
            if (stmt->parameterTypes[i]->singleObjectType() == SingleObjectType::Void) {
                TypeError::typeNotAllowed(stmt->parameterTypes[i], stmt->parameters[i]->line, stmt->parameters[i]->column);
            }
        }
        returnValueType = stmt->objectType;
        curBlock = stmt->block;
        checkBlock(program->varTable);
        curBlock = nullptr;
    }

    void TypeChecker::checkBlock(VarTable *outer) {
        curBlock->varTable = new VarTable(outer);
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
                checkBlock(temp->varTable);
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


} // karl