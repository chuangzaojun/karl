#include "generator.hpp"

namespace karl {
    namespace compiler {
        compiler::Generator::Generator(Program *program) {
            this->program = program;
            this->byteCode = new bytecode::ByteCode();
        }

        bytecode::ByteCode *Generator::generateBytecode() {
            byteCode->maxGlobalVarNum = program->varTable->globalVarNum();
            byteCode->funcInfos.push_back(new bytecode::FuncInfo);
            curFuncInfo = byteCode->funcInfos[0];
            curStackSize = 0;
            for (Stmt *stmt: program->stmts) {
                if (stmt->stmtType() == StmtType::VarDef) {
                    generateGlobalVarDef((VarDefStmt *) stmt);
                }
            }
            for (Stmt *stmt: program->stmts) {
                if (stmt->stmtType() == StmtType::FuncDef) {
                    if (((IdentifierExpr *) ((FuncDefStmt *) stmt)->name)->identifier == "main") {
                        curFuncInfo = byteCode->funcInfos[0];
                    } else {
                        byteCode->funcInfos.push_back(new bytecode::FuncInfo());
                        curFuncInfo = byteCode->funcInfos[byteCode->funcInfos.size() - 1];
                    }
                    generateFuncDef((FuncDefStmt *) stmt);
                }
            }
            return byteCode;
        }

        int Generator::writeIntroduction(bytecode::Introduction *introduction) {
            curFuncInfo->introductions.push_back(introduction);
            switch (introduction->opCode) {
                case bytecode::OpCode::PushIntConst:
                case bytecode::OpCode::PushCharConst:
                case bytecode::OpCode::PushStringConst:
                case bytecode::OpCode::PushTrue:
                case bytecode::OpCode::PushFalse:
                case bytecode::OpCode::PushGlobalVar:
                case bytecode::OpCode::PushLocalVar:
                    curStackSize++;
                    break;
                case bytecode::OpCode::IfTrueGoto:
                case bytecode::OpCode::IfFalseGoto:
                case bytecode::OpCode::Pop:
                case bytecode::OpCode::Minus:
                case bytecode::OpCode::Add:
                case bytecode::OpCode::Mul:
                case bytecode::OpCode::Div:
                case bytecode::OpCode::Mod:
                case bytecode::OpCode::LessThan:
                case bytecode::OpCode::LessEqual:
                case bytecode::OpCode::GreaterThan:
                case bytecode::OpCode::GreaterEqual:
                case bytecode::OpCode::Equal:
                case bytecode::OpCode::NotEqual:
                case bytecode::OpCode::And:
                case bytecode::OpCode::Or:
                case bytecode::OpCode::BAnd:
                case bytecode::OpCode::BOr:
                case bytecode::OpCode::BXor:
                case bytecode::OpCode::LMove:
                case bytecode::OpCode::RMove:
                case bytecode::OpCode::GetArrayIndex:
                case bytecode::OpCode::SetArrayIndex:
                case bytecode::OpCode::Return:
                    curStackSize--;
                    break;
                case bytecode::OpCode::NativeFuncCall:
                case bytecode::OpCode::FuncCall:
                case bytecode::OpCode::MakeArray:
                    curStackSize -= ((bytecode::Introduction1Number *) introduction)->num;
                    curStackSize++;
                    break;
            }
            if (curStackSize > curFuncInfo->maxStackSize) {
                curFuncInfo->maxStackSize = curStackSize;
            }
            if (introduction->opCode == bytecode::OpCode::PushLocalVar || introduction->opCode == bytecode::OpCode::SetLocalVar) {
                if (((bytecode::Introduction1Number *) introduction)->num > curFuncInfo->maxLocalVarNum) {
                    curFuncInfo->maxLocalVarNum = ((bytecode::Introduction1Number *) introduction)->num;
                }
            }
            return curFuncInfo->introductions.size() - 1;
        }

        int Generator::writeIntConst(int value) {
            byteCode->intConsts.push_back(value);
            return byteCode->intConsts.size() - 1;
        }

        int Generator::writeCharConst(char value) {
            byteCode->charConsts.push_back(value);
            return byteCode->charConsts.size() - 1;
        }

        int Generator::writeStringConst(std::string value) {
            byteCode->stringConsts.push_back(value);
            return byteCode->stringConsts.size() - 1;
        }
    }
}