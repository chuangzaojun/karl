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
            curFuncInfo = nullptr;
            for (Stmt *stmt: program->stmts) {
                if (stmt->stmtType() == StmtType::FuncDef) {
                    generateFuncDef((FuncDefStmt *) stmt);
                }
            }
            return bytecode;
        }

        int Generator::writeInstruction(bytecode::Instruction *introduction) {
            curFuncInfo->instructions.push_back(introduction);
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
                case bytecode::OpCode::GotoIfTrue:
                case bytecode::OpCode::GotoIfFalse:
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
                    curStackSize -= ((bytecode::Instruction1Number *) introduction)->num;
                    curStackSize++;
                    break;
            }
            if (curStackSize > curFuncInfo->maxStackSize) {
                curFuncInfo->maxStackSize = curStackSize;
            }
            if (introduction->opCode == bytecode::OpCode::PushLocalVar ||
                introduction->opCode == bytecode::OpCode::SetLocalVar) {
                if (((bytecode::Instruction1Number *) introduction)->num + 1 > curFuncInfo->maxLocalVarNum) {
                    curFuncInfo->maxLocalVarNum = ((bytecode::Instruction1Number *) introduction)->num + 1;
                }
            }
            return curFuncInfo->instructions.size() - 1;
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
                    writeNullValue(stmt->types[i]);
                } else {
                    generateExpr(stmt->initValues[i]);
                }
                writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::SetGlobalVar,
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
            generateBlock();
            curBlock = nullptr;
            if (stmt->objectType->singleObjectType() == SingleObjectType::Void) {
                writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::ReturnNull));
            } else {
                writeNullValue(stmt->objectType);
                writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::Return));
            }
            curFuncInfo = nullptr;
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
            writeInstruction(new bytecode::Instruction0Number(opToOpCode[expr->op]));
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
            writeInstruction(new bytecode::Instruction0Number(opToOpCode[expr->op]));
        }

        void Generator::generateAssignExpr(AssignExpr *expr) {
            if (expr->left->exprType() == ExprType::ArrayIndex) {
                generateExpr(((ArrayIndexExpr *) expr->left)->array);
                generateExpr(((ArrayIndexExpr *) expr->left)->index);
                generateExpr(expr->right);
                writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::SetArrayIndex));
            } else {
                generateExpr(expr->right);
                if (curBlock->varTable->isLocalVar(((IdentifierExpr *) expr->left)->identifier)) {
                    writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::SetLocalVar,
                                                                      curBlock->varTable->getIndex(
                                                                              ((IdentifierExpr *) expr->left)
                                                                                      ->identifier)));
                } else {
                    writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::SetGlobalVar,
                                                                      program->varTable->getIndex(
                                                                              ((IdentifierExpr *) expr->left)
                                                                                      ->identifier)));
                }
            }
        }

        void Generator::generateIdentifierExpr(IdentifierExpr *expr) {
            if (curBlock->varTable->isLocalVar(expr->identifier)) {
                writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::PushLocalVar,
                                                                  curBlock->varTable->getIndex(expr->identifier)));
            } else {
                writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::PushGlobalVar,
                                                                  program->varTable->getIndex(expr->identifier)));
            }
        }

        void Generator::generateFuncCallExpr(FuncCallExpr *expr) {
            for (int i = expr->arguments.size() - 1; i >= 0; i--) {
                generateExpr(expr->arguments[i]);
            }
            if (((IdentifierExpr *) expr->name)->identifier == "print") {
                writeInstruction(new bytecode::Instruction2Number(bytecode::OpCode::NativeFuncCall, expr->arguments
                        .size(), 0));
            } else {
                writeInstruction(new bytecode::Instruction2Number(bytecode::OpCode::FuncCall, expr->arguments.size(),
                                                                  program->funcTable->getIndex(
                                                                          ((IdentifierExpr *) expr->name)->identifier)));
            }
        }

        void Generator::generateArrayIndexExpr(ArrayIndexExpr *expr) {
            generateExpr(expr->array);
            generateExpr(expr->index);
            writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::GetArrayIndex));
        }

        void Generator::generateArrayLiteralExpr(ArrayLiteralExpr *expr) {
            for (int i = expr->exprs.size() - 1; i >= 0; i--) {
                generateExpr(expr->exprs[i]);
            }
            writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::MakeArray, expr->exprs.size()));
        }

        void Generator::generateIntExpr(IntExpr *expr) {
            writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::PushIntConst, writeIntConst(
                    (expr->value))));
        }

        void Generator::generateCharExpr(CharExpr *expr) {
            writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::PushCharConst, writeCharConst(
                    (expr->value))));
        }

        void Generator::generateStringExpr(StringExpr *expr) {
            writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::PushStringConst, writeStringConst(
                    (expr->value))));
        }

        void Generator::generateBoolExpr(BoolExpr *expr) {
            if (expr->value == true) {
                writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::PushTrue));
            } else {
                writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::PushFalse));
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
            writeInstruction(new bytecode::Instruction0Number(typeToOpCode[expr->targetType]));
        }

        void Generator::writeNullValue(ObjectType *type) {
            switch (type->singleObjectType()) {
                case SingleObjectType::Int:
                    writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::PushIntConst,
                                                                      writeIntConst(0)));
                    break;
                case SingleObjectType::Char:
                    writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::PushCharConst,
                                                                      writeCharConst(' ')));
                    break;
                case SingleObjectType::String:
                    writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::PushStringConst,
                                                                      writeStringConst("")));
                    break;
                case SingleObjectType::Bool:
                    writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::PushFalse));
                    break;
                case SingleObjectType::Array:
                    for (int i = 0; i < ((ArrayObject *) type)->memberNum; i++) {
                        writeNullValue(((ArrayObject *) type)->memberType);
                    }
                    writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::MakeArray, ((ArrayObject *)
                            type)->memberNum));
            }
        }

        void Generator::generateStmt(Stmt *stmt) {
            switch (stmt->stmtType()) {
                case StmtType::VarDef:
                    generateLocalVarDefStmt((VarDefStmt *) stmt);
                    break;
                case StmtType::If:
                    generateIfStmt((IfStmt *) stmt);
                    break;
                case StmtType::While:
                    generateWhileStmt((WhileStmt *) stmt);
                    break;
                case StmtType::Expr:
                    generateExprStmt((ExprStmt *) stmt);
                    break;
                case StmtType::Break:
                    generateBreakStmt((BreakStmt *) stmt);
                    break;
                case StmtType::Continue:
                    generateContinueStmt((ContinueStmt *) stmt);
                    break;
                case StmtType::Return:
                    generateReturnStmt((ReturnStmt *) stmt);
                    break;
                case StmtType::Block:
                    Block *temp = curBlock;
                    curBlock = (Block *) stmt;
                    generateBlock();
                    curBlock = temp;
                    break;
            }
        }

        void Generator::generateBlock() {
            for (Stmt *stmt: curBlock->stmts) {
                generateStmt(stmt);
            }
        }

        void Generator::generateLocalVarDefStmt(VarDefStmt *stmt) {
            for (int i = 0; i < stmt->vars.size(); i++) {
                if (stmt->initValues[i] == nullptr) {
                    writeNullValue(stmt->types[i]);
                } else {
                    generateExpr(stmt->initValues[i]);
                }
                writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::SetLocalVar,
                                                                  curBlock->varTable->getIndex(
                                                                          ((IdentifierExpr *) stmt->vars[i])->identifier)));
            }
        }

        void Generator::generateIfStmt(IfStmt *stmt) {
            std::vector<int> gotoIntroductionIndexes;
            for (int i = 0; i < stmt->conditions.size(); i++) {
                generateExpr(stmt->conditions[i]);
                int introductionIndexTemp = writeInstruction(new bytecode::Instruction1Number
                                                                     (bytecode::OpCode::GotoIfFalse, 0));
                Block *temp = curBlock;
                curBlock = stmt->blocks[i];
                generateBlock();
                curBlock = temp;
                gotoIntroductionIndexes.push_back(writeInstruction(new bytecode::Instruction1Number
                                                                           (bytecode::OpCode::Goto, 0)));
                ((bytecode::Instruction1Number *) curFuncInfo->instructions[introductionIndexTemp])->num =
                        curIntroductionNum();
            }
            if (stmt->conditions.size() < stmt->blocks.size()) {
                Block *temp = curBlock;
                curBlock = stmt->blocks[stmt->blocks.size() - 1];
                generateBlock();
                curBlock = temp;
            }
            for (int i: gotoIntroductionIndexes) {
                ((bytecode::Instruction1Number *) curFuncInfo->instructions[i])->num = curIntroductionNum();
            }
        }

        int Generator::curIntroductionNum() {
            return curFuncInfo->instructions.size();
        }

        void Generator::generateWhileStmt(WhileStmt *stmt) {
            int beginIndex = curIntroductionNum();
            generateExpr(stmt->condition);
            int introductionIndexTemp = writeInstruction(new bytecode::Instruction1Number
                                                                 (bytecode::OpCode::GotoIfFalse, 0));
            Block *temp = curBlock;
            curBlock = stmt->block;
            generateBlock();
            curBlock = temp;
            writeInstruction(new bytecode::Instruction1Number(bytecode::OpCode::Goto, beginIndex));
            for (int i: stmt->block->breakIntroductionIndexes) {
                ((bytecode::Instruction1Number *) curFuncInfo->instructions[i])->num = curIntroductionNum();
            }
            for (int i: stmt->block->continueIntroductionIndexes) {
                ((bytecode::Instruction1Number *) curFuncInfo->instructions[i])->num = beginIndex;
            }
            ((bytecode::Instruction1Number *) curFuncInfo->instructions[introductionIndexTemp])->num = curIntroductionNum();
        }

        void Generator::generateExprStmt(ExprStmt *stmt) {
            generateExpr(stmt->expr);
            if (stmt->expr->objectType->singleObjectType() != SingleObjectType::Void) {
                writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::Pop));
            }
        }

        void Generator::generateBreakStmt(BreakStmt *stmt) {
            stmt->loopBlock->breakIntroductionIndexes.push_back(writeInstruction(new bytecode::Instruction1Number
                                                                                         (bytecode::OpCode::Goto, 0)));
        }

        void Generator::generateContinueStmt(ContinueStmt *stmt) {
            stmt->loopBlock->continueIntroductionIndexes.push_back(writeInstruction(new bytecode::Instruction1Number
                                                                                            (bytecode::OpCode::Goto, 0)));
        }

        void Generator::generateReturnStmt(ReturnStmt *stmt) {
            if (stmt->expr != nullptr) {
                generateExpr(stmt->expr);
                writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::Return));
            } else {
                writeInstruction(new bytecode::Instruction0Number(bytecode::OpCode::ReturnNull));
            }
        }
    }
}