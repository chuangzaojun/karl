#include "generator.hpp"

namespace karl {
    namespace compiler {
        compiler::Generator::Generator(Program *program) {
            this->program = program;
            this->bytecode = new bytecode::Bytecode();
        }

        bytecode::Bytecode *Generator::generateBytecode() {
            bytecode->maxGlobalVarNum = program->varTable->globalVarNum();
            bytecode->funcInfos.push_back(new bytecode::FuncInfo);
            curFuncInfo = bytecode->funcInfos[0];
            curStackSize = 0;
            for (Stmt *stmt: program->stmts) {
                if (stmt->stmtType() == StmtType::VarDef) {
                    generateGlobalVarDef((VarDefStmt *) stmt);
                }
            }
            for (Stmt *stmt: program->stmts) {
                if (stmt->stmtType() == StmtType::FuncDef) {
                    generateFuncDef((FuncDefStmt *) stmt);
                }
            }
            return bytecode;
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
            if (introduction->opCode == bytecode::OpCode::PushLocalVar ||
                introduction->opCode == bytecode::OpCode::SetLocalVar) {
                if (((bytecode::Introduction1Number *) introduction)->num > curFuncInfo->maxLocalVarNum) {
                    curFuncInfo->maxLocalVarNum = ((bytecode::Introduction1Number *) introduction)->num;
                }
            }
            return curFuncInfo->introductions.size() - 1;
        }

        int Generator::writeIntConst(int value) {
            bytecode->intConsts.push_back(value);
            return bytecode->intConsts.size() - 1;
        }

        int Generator::writeCharConst(char value) {
            bytecode->charConsts.push_back(value);
            return bytecode->charConsts.size() - 1;
        }

        int Generator::writeStringConst(std::string value) {
            bytecode->stringConsts.push_back(value);
            return bytecode->stringConsts.size() - 1;
        }

        void Generator::generateGlobalVarDef(VarDefStmt *stmt) {
            for (int i = 0; i < stmt->vars.size(); i++) {
                if (stmt->initValues[i] == nullptr) {
                    continue;
                }
                generateExpr(stmt->initValues[i]);
                writeIntroduction(new bytecode::Introduction1Number(bytecode::OpCode::SetGlobalVar,
                                                                    program->varTable->getIndex(
                                                                            ((IdentifierExpr *) stmt->vars[i])->identifier)));
            }
        }

        void Generator::generateFuncDef(FuncDefStmt *stmt) {
            if (((IdentifierExpr *) stmt->name)->identifier == "main") {
                curFuncInfo = bytecode->funcInfos[0];
            } else {
                bytecode->funcInfos.push_back(new bytecode::FuncInfo());
                curFuncInfo = bytecode->funcInfos[bytecode->funcInfos.size() - 1];
            }
            curBlock = stmt->block;
            generateBlock(stmt->block);
        }

        void Generator::generateExpr(Expr *expr) {
            switch (expr->exprType()) {
                case ExprType::Prefix:
                    generatePrefixExpr((PrefixExpr *) expr);
                    break;
                case ExprType::Binary:
                    generateBinaryExpr((BinaryExpr *) expr);
                    break;
                case ExprType::Assign:
                    generateAssignExpr((AssignExpr *) expr);
                    break;
                case ExprType::Identifier:
                    generateIdentifierExpr((IdentifierExpr *) expr);
                    break;
                case ExprType::FuncCall:
                    generateFuncCallExpr((FuncCallExpr *) expr);
                    break;
                case ExprType::ArrayIndex:
                    generateArrayIndexExpr((ArrayIndexExpr *) expr);
                    break;
                case ExprType::ArrayLiteral:
                    generateArrayLiteralExpr((ArrayLiteralExpr *) expr);
                    break;
                case ExprType::Int:
                    generateIntExpr((IntExpr *) expr);
                    break;
                case ExprType::Char:
                    generateCharExpr((CharExpr *) expr);
                    break;
                case ExprType::String:
                    generateStringExpr((StringExpr *) expr);
                    break;
                case ExprType::Bool:
                    generateBoolExpr((BoolExpr *) expr);
                case ExprType::TypeConversion:
                    generateTypeConversionExpr((TypeConversionExpr *) expr);
                    break;
            }
        }

        void Generator::generatePrefixExpr(PrefixExpr *expr) {
            std::map<OpType, bytecode::OpCode> opToOpCode = {
                    {OpType::Minus, bytecode::OpCode::PreMinus},
                    {OpType::Not,   bytecode::OpCode::Not},
                    {OpType::BNot,  bytecode::OpCode::BNot}
            };
            generateExpr(expr->right);
            writeIntroduction(new bytecode::Introduction0Number(opToOpCode[expr->op]));
        }

        void Generator::generateBinaryExpr(BinaryExpr *expr) {
            std::map<OpType, bytecode::OpCode> opToOpCode = {
                    {OpType::Minus,        bytecode::OpCode::Minus},
                    {OpType::Add,          bytecode::OpCode::Add},
                    {OpType::Mul,          bytecode::OpCode::Mul},
                    {OpType::Div,          bytecode::OpCode::Div},
                    {OpType::Mod,          bytecode::OpCode::Mod},
                    {OpType::LessThan,     bytecode::OpCode::LessThan},
                    {OpType::LessEqual,    bytecode::OpCode::LessEqual},
                    {OpType::GreaterThan,  bytecode::OpCode::GreaterThan},
                    {OpType::GreaterEqual, bytecode::OpCode::GreaterEqual},
                    {OpType::Equal,        bytecode::OpCode::Equal},
                    {OpType::NotEqual,     bytecode::OpCode::NotEqual},
                    {OpType::And,          bytecode::OpCode::And},
                    {OpType::Or,           bytecode::OpCode::Or},
                    {OpType::BAnd,         bytecode::OpCode::BAnd},
                    {OpType::BOr,          bytecode::OpCode::BOr},
                    {OpType::LMove,        bytecode::OpCode::LMove},
                    {OpType::RMove,        bytecode::OpCode::RMove}
            };
            generateExpr(expr->left);
            generateExpr(expr->right);
            writeIntroduction(new bytecode::Introduction0Number(opToOpCode[expr->op]));
        }

        void Generator::generateAssignExpr(AssignExpr *expr) {
            if (expr->left->exprType() == ExprType::ArrayIndex) {
                generateExpr(((ArrayIndexExpr *) expr->left)->array);
                generateExpr(((ArrayIndexExpr *) expr->left)->index);
                generateExpr(expr->right);
                writeIntroduction(new bytecode::Introduction0Number(bytecode::OpCode::SetArrayIndex));
            } else {
                generateExpr(expr->right);
                if (curBlock->varTable->isLocalVar(((IdentifierExpr *) expr->left)->identifier)) {
                    writeIntroduction(new bytecode::Introduction1Number(bytecode::OpCode::SetLocalVar,
                                                                        curBlock->varTable->getIndex(
                                                                                ((IdentifierExpr *) expr->left)
                                                                                        ->identifier)));
                } else {
                    writeIntroduction(new bytecode::Introduction1Number(bytecode::OpCode::SetGlobalVar,
                                                                        program->varTable->getIndex(
                                                                                ((IdentifierExpr *) expr->left)
                                                                                        ->identifier)));
                }
            }
        }

        void Generator::generateIdentifierExpr(IdentifierExpr *expr) {
            if (curBlock->varTable->isLocalVar(expr->identifier)) {
                writeIntroduction(new bytecode::Introduction1Number(bytecode::OpCode::PushLocalVar,
                                                                    curBlock->varTable->getIndex(expr->identifier)));
            } else {
                writeIntroduction(new bytecode::Introduction1Number(bytecode::OpCode::PushGlobalVar,
                                                                    program->varTable->getIndex(expr->identifier)));
            }
        }

        void Generator::generateFuncCallExpr(FuncCallExpr *expr) {
            for (int i = expr->arguments.size() - 1; i >= 0; i--) {
                generateExpr(expr->arguments[i]);
            }
            if (((IdentifierExpr *) expr->name)->identifier == "print") {
                writeIntroduction(new bytecode::Introduction2Number(bytecode::OpCode::NativeFuncCall, expr->arguments
                        .size(), 0));
            }
            writeIntroduction(new bytecode::Introduction2Number(bytecode::OpCode::FuncCall, expr->arguments.size(),
                                                                program->funcTable->getIndex(
                                                                        ((IdentifierExpr *) expr->name)->identifier)));
        }

        void Generator::generateArrayIndexExpr(ArrayIndexExpr *expr) {
            generateExpr(expr->array);
            generateExpr(expr->index);
            writeIntroduction(new bytecode::Introduction0Number(bytecode::OpCode::GetArrayIndex));
        }

        void Generator::generateArrayLiteralExpr(ArrayLiteralExpr *expr) {
            for (int i = expr->exprs.size() - 1; i >= 0; i--) {
                generateExpr(expr->exprs[i]);
            }
            writeIntroduction(new bytecode::Introduction1Number(bytecode::OpCode::MakeArray, expr->exprs.size()));
        }

        void Generator::generateIntExpr(IntExpr *expr) {
            writeIntroduction(new bytecode::Introduction1Number(bytecode::OpCode::PushIntConst, writeIntConst(
                    (expr->value))));
        }

        void Generator::generateCharExpr(CharExpr *expr) {
            writeIntroduction(new bytecode::Introduction1Number(bytecode::OpCode::PushCharConst, writeCharConst(
                    (expr->value))));
        }

        void Generator::generateStringExpr(StringExpr *expr) {
            writeIntroduction(new bytecode::Introduction1Number(bytecode::OpCode::PushStringConst, writeStringConst(
                    (expr->value))));
        }

        void Generator::generateBoolExpr(BoolExpr *expr) {
            if (expr->value == true) {
                writeIntroduction(new bytecode::Introduction0Number(bytecode::OpCode::PushTrue));
            } else {
                writeIntroduction(new bytecode::Introduction0Number(bytecode::OpCode::PushFalse));
            }
        }

        void Generator::generateTypeConversionExpr(TypeConversionExpr *expr) {
            std::map<SingleObjectType, bytecode::OpCode> typeToOpCode = {
                    {SingleObjectType::Int,    bytecode::OpCode::TypeToInt},
                    {SingleObjectType::Bool,   bytecode::OpCode::TypeToBool},
                    {SingleObjectType::String, bytecode::OpCode::TypeToString},
                    {SingleObjectType::Char,   bytecode::OpCode::TypeToChar}
            };
            generateExpr(expr->expr);
            writeIntroduction(new bytecode::Introduction0Number(typeToOpCode[expr->targetType]));
        }
    }
}