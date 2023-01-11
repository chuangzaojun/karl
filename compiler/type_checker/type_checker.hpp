#ifndef KARL_TYPE_CHECKER_HPP
#define KARL_TYPE_CHECKER_HPP

#include "../ast/program.hpp"

namespace karl {

    namespace compiler {

        class TypeChecker {
        private:
            Program *program;
            Block *curBlock;
            Block *curLoopBlock;
            ObjectType *returnValueType;

            void checkGlobalVarDef(VarDefStmt *stmt);
            void checkFuncDef(FuncDefStmt *stmt);

            void checkType(ObjectType *type, int line, int column);

            void checkBlock(VarTable *outer); // this function does not change curBlock & curLoopBlock

            void checkStmt(Stmt *stmt);
            void checkLocalVarDefStmt(VarDefStmt *stmt);
            void checkIfStmt(IfStmt *stmt);
            void checkWhileStmt(WhileStmt *stmt);
            void checkExprStmt(ExprStmt *stmt);
            void checkBreakStmt(BreakStmt *stmt);
            void checkContinueStmt(ContinueStmt *stmt);
            void checkReturnStmt(ReturnStmt *stmt);

            void checkExpr(Expr *expr, VarTable *varTable);
            void checkBinaryExpr(BinaryExpr *expr, VarTable *varTable);
            void checkPrefixExpr(PrefixExpr *expr, VarTable *varTable);
            void checkAssignExpr(AssignExpr *expr, VarTable *varTable);
            void checkIntExpr(IntExpr *expr, VarTable *varTable);
            void checkCharExpr(CharExpr *expr, VarTable *varTable);
            void checkStringExpr(StringExpr *expr, VarTable *varTable);
            void checkBoolExpr(BoolExpr *expr, VarTable *varTable);
            void checkIdentifierExpr(IdentifierExpr *expr, VarTable *varTable);
            void checkFuncCallExpr(FuncCallExpr *expr, VarTable *varTable);
            void checkTypeConversionExpr(TypeConversionExpr *expr, VarTable *varTable);
            void checkArrayIndexExpr(ArrayIndexExpr *expr, VarTable *varTable);
            void checkArrayLiteralExpr(ArrayLiteralExpr *expr, VarTable *varTable);


        public:
            TypeChecker(Program *program);
            void checkProgram();
        };
    }
}

#endif //KARL_TYPE_CHECKER_HPP
