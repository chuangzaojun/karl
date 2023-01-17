#ifndef KARL_GENERATOR_HPP
#define KARL_GENERATOR_HPP

#include "../../bytecode/bytecode.hpp"
#include "../ast/program.hpp"

namespace karl {
    namespace compiler {
        class Generator {
        private:
            Program *program;
            Block *curBlock;
            bytecode::Bytecode *bytecode;
            bytecode::FuncInfo *curFuncInfo;
            int curStackSize;

            int writeIntroduction(bytecode::Introduction *introduction);
            int writeIntConst(int value);
            int writeCharConst(char value);
            int writeStringConst(std::string value);
            int curIntroductionNum();

            void writeNullValue(ObjectType *type);

            void generateGlobalVarDef(VarDefStmt *stmt);
            void generateFuncDef(FuncDefStmt *stmt);

            void generateStmt(Stmt *stmt);
            void generateBlock(); // this function does not change the var curBlock
            void generateLocalVarDefStmt(VarDefStmt *stmt);
            void generateIfStmt(IfStmt *stmt);
            void generateWhileStmt(WhileStmt *stmt);
            void generateExprStmt(ExprStmt *stmt);
            void generateBreakStmt(BreakStmt *stmt);
            void generateContinueStmt(ContinueStmt *stmt);
            void generateReturnStmt(ReturnStmt *stmt);

            void generateExpr(Expr *expr);
            void generatePrefixExpr(PrefixExpr *expr);
            void generateBinaryExpr(BinaryExpr *expr);
            void generateAssignExpr(AssignExpr *expr);
            void generateIdentifierExpr(IdentifierExpr *expr);
            void generateFuncCallExpr(FuncCallExpr *expr);
            void generateArrayIndexExpr(ArrayIndexExpr *expr);
            void generateArrayLiteralExpr(ArrayLiteralExpr *expr);
            void generateIntExpr(IntExpr *expr);
            void generateCharExpr(CharExpr *expr);
            void generateStringExpr(StringExpr *expr);
            void generateBoolExpr(BoolExpr *expr);
            void generateTypeConversionExpr(TypeConversionExpr *expr);

        public:
            Generator(Program *program);
            bytecode::Bytecode *generateBytecode();
        };
    }
}

#endif //KARL_GENERATOR_HPP
