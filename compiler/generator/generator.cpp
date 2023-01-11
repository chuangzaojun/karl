#include "generator.hpp"

namespace karl {
    namespace compiler {
        compiler::Generator::Generator(Program *program) {
            this->program = program;
        }

        bytecode::ByteCode *Generator::generateBytecode() {
            bytecode::ByteCode *byteCode = new bytecode::ByteCode();
            byteCode->maxGlobalVarNum = program->varTable->globalVarNum();
            byteCode->funcInfos.push_back(new bytecode::FuncInfo);
            curFuncInfo = byteCode->funcInfos[0];
            for (Stmt *stmt: program->stmts) {
                if (stmt->stmtType() == StmtType::VarDef) {

                }
            }
            curFuncInfo = nullptr;
        }

        int Generator::writeIntroduction(bytecode::Introduction *introduction) {
            curFuncInfo->introductions.push_back(introduction);
            return curFuncInfo->introductions.size() - 1;
        }
    }
}