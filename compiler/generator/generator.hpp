#ifndef KARL_GENERATOR_HPP
#define KARL_GENERATOR_HPP

#include "../../bytecode/byte_code.hpp"
#include "../ast/program.hpp"

namespace karl {
    namespace compiler {
        class Generator {
        private:
            Program *program;
            bytecode::ByteCode *byteCode;
            bytecode::FuncInfo *curFuncInfo;
            int curStackSize;

            int writeIntroduction(bytecode::Introduction *introduction);
            int writeIntConst(int value);
            int writeCharConst(char value);
            int writeStringConst(std::string value);

            void generateGlobalVarDef(VarDefStmt *stmt);
            void generateFuncDef(FuncDefStmt *stmt);

            void generateExpr(Expr *expr);
            void generatePrefixExpr(PrefixExpr *expr);
            void generateBinaryExpr(BinaryExpr *expr);
        public:
            Generator(Program *program);
            bytecode::ByteCode *generateBytecode();
        };
    }
}

#endif //KARL_GENERATOR_HPP
