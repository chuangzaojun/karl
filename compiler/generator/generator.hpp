#ifndef KARL_GENERATOR_HPP
#define KARL_GENERATOR_HPP

#include "../../bytecode/bytecode.hpp"
#include "../ast/program.hpp"

namespace karl {
    namespace compiler {
        class Generator {
        private:
            Program *program;
            bytecode::FuncInfo *curFuncInfo;

            int writeIntroduction(bytecode::Introduction *introduction);

            void generateGlobalVarDef(VarDefStmt *stmt);
            void generateFuncDef(FuncDefStmt *stmt);


        public:
            Generator(Program *program);
            bytecode::ByteCode *generateBytecode();
        };
    }
}

#endif //KARL_GENERATOR_HPP
