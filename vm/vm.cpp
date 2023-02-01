#include "vm.hpp"

namespace karl {
    namespace vm {

        void VM::pushFrame(bytecode::FuncInfo *funcInfo) {
            Frame *frame = new Frame(funcInfo);
            frames.push_back(frame);
            curFrame = frame;
        }

        VM::VM(bytecode::Bytecode *bytecode, Heap *heap) {
            this->bytecode = bytecode;
            this->heap = heap;
            globalVars = std::vector<Object *>(bytecode->maxGlobalVarNum);
        }

        void VM::popFrame() {
            frames.pop_back();
            curFrame = frames.back();
        }

        void VM::runFuncCall(int argumentNum, int funcIndex) {
            std::vector<Object *> arguments(argumentNum);
            for (int i = 0; i < argumentNum; i++) {
                arguments[i] = curFrame->pop();
            }
            pushFrame(bytecode->funcInfos[funcIndex]);
            for (int i = 0; i < argumentNum; i++) {
                curFrame->setVar(i, arguments[i]);
            }
            curFrame->setPc(-1);
        }

        void VM::runNativeFuncCall(int argumentNum, int funcIndex) {
            std::vector<Object *> arguments(argumentNum);
            for (int i = 0; i < argumentNum; i++) {
                arguments[i] = curFrame->pop();
                printf("%s", arguments[i]->getStringValue().data());
            }
        }

        void VM::runPushIntConst(int index) {
            heap->define(curFrame->push(new IntObject(bytecode->intConsts[index])));
        }

        void VM::runPushCharConst(int index) {
            heap->define(curFrame->push(new CharObject(bytecode->charConsts[index])));
        }

        void VM::runPushStringConst(int index) {
            heap->define(curFrame->push(new StringObject(bytecode->stringConsts[index])));
        }

        void VM::runPushGlobalVar(int index) {
            curFrame->push(globalVars[index]);
        }

        void VM::runPushLocalVar(int index) {
            curFrame->push(curFrame->getVar(index));
        }

        void VM::runSetGlobalVar(int index) {
            globalVars[index] = curFrame->pop();
            curFrame->push(globalVars[index]);
        }

        void VM::runSetLocalVar(int index) {
            curFrame->setVar(index, curFrame->pop());
            curFrame->push(curFrame->getVar(index));
        }

        void VM::runGotoIfTrue(int newPc) {
            if (curFrame->pop()->getBoolValue() == true) {
                curFrame->setPc(newPc - 1);
            }
        }

        void VM::runGotoIfFalse(int newPc) {
            if (curFrame->pop()->getBoolValue() == false) {
                curFrame->setPc(newPc - 1);
            }
        }

        void VM::runGoto(int newPc) {
            curFrame->setPc(newPc - 1);
        }

        void VM::runMakeArray(int size) {
            ArrayObject *object = new ArrayObject(size);
            for (int i = 0; i < size; i++) {
                object->value[i] = curFrame->pop();
            }
            heap->define(curFrame->push(object));
        }

        void VM::runReturn() {
            Object *returnValue = curFrame->pop();
            popFrame();
            curFrame->push(returnValue);
        }

        void VM::runReturnNull() {
            popFrame();
        }

        void VM::runPushTrue() {
            heap->define(curFrame->push(new BoolObject(true)));
        }

        void VM::runPushFalse() {
            heap->define(curFrame->push(new BoolObject(false)));
        }

        void VM::runPop() {
            curFrame->pop();
        }

        void VM::runSetArrayIndex() {
            Object *value = curFrame->pop();
            int index = ((IntObject *) curFrame->pop())->value;
            ArrayObject *array = (ArrayObject *) curFrame->pop();
            array->value[index] = value;
            curFrame->push(array);
        }

        void VM::runGetArrayIndex() {
            int index = ((IntObject *) curFrame->pop())->value;
            ArrayObject *array = (ArrayObject *) curFrame->pop();
            Object *value = array->value[index];
            curFrame->push(value);
        }

        void VM::runMinus() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a - b)));
        }

        void VM::runAdd() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a + b)));
        }

        void VM::runMul() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a * b)));
        }

        void VM::runDiv() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a / b)));
        }

        void VM::runMod() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a % b)));
        }

        void VM::runLessThan() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new BoolObject(a < b)));
        }

        void VM::runLessEqual() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new BoolObject(a <= b)));
        }

        void VM::runGreaterThan() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new BoolObject(a > b)));
        }

        void VM::runGreaterEqual() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new BoolObject(a >= b)));
        }

        void VM::runEqual() {
            Object *object = curFrame->pop();
            if (object->type() == SingleObjectType::String) {
                std::string b = object->getStringValue();
                std::string a = curFrame->pop()->getStringValue();
                heap->define(curFrame->push(new BoolObject(a == b)));
            } else {
                int b = object->getIntValue();
                int a = curFrame->pop()->getIntValue();
                heap->define(curFrame->push(new BoolObject(a == b)));
            }
        }

        void VM::runNotEqual() {
            Object *object = curFrame->pop();
            if (object->type() == SingleObjectType::String) {
                std::string b = object->getStringValue();
                std::string a = curFrame->pop()->getStringValue();
                heap->define(curFrame->push(new BoolObject(a != b)));
            } else {
                int b = object->getIntValue();
                int a = curFrame->pop()->getIntValue();
                heap->define(curFrame->push(new BoolObject(a != b)));
            }
        }

        void VM::runAnd() {
            bool b = curFrame->pop()->getBoolValue();
            bool a = curFrame->pop()->getBoolValue();
            heap->define(curFrame->push(new BoolObject(a && b)));
        }

        void VM::runOr() {
            bool b = curFrame->pop()->getBoolValue();
            bool a = curFrame->pop()->getBoolValue();
            heap->define(curFrame->push(new BoolObject(a || b)));
        }

        void VM::runBAnd() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a & b)));
        }

        void VM::runBOr() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a | b)));
        }

        void VM::runBXor() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a ^ b)));
        }

        void VM::runLMove() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a << b)));
        }

        void VM::runRMove() {
            int b = curFrame->pop()->getIntValue();
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(a >> b)));
        }

        void VM::runPreMinus() {
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(-a)));
        }

        void VM::runNot() {
            bool a = curFrame->pop()->getBoolValue();
            heap->define(curFrame->push(new BoolObject(!a)));
        }

        void VM::runBNot() {
            int a = curFrame->pop()->getIntValue();
            heap->define(curFrame->push(new IntObject(~a)));
        }

        void VM::runTypeToInt() {
            Object *object = curFrame->pop();
            heap->define(curFrame->push(new IntObject(object->getIntValue())));
        }

        void VM::runTypeToString() {
            Object *object = curFrame->pop();
            heap->define(curFrame->push(new StringObject(object->getStringValue())));
        }

        void VM::runTypeToChar() {
            Object *object = curFrame->pop();
            heap->define(curFrame->push(new CharObject(object->getCharValue())));
        }

        void VM::runTypeToBool() {
            Object *object = curFrame->pop();
            heap->define(curFrame->push(new BoolObject(object->getBoolValue())));
        }

        void VM::run() {
            pushFrame(bytecode->funcInfos[0]);
            while (!frames.empty()) {
                if (curFrame->curInstruction()->introductionType() == bytecode::InstructionType::With2Number) {
                    int numA = ((bytecode::Instruction2Number *) curFrame->curInstruction())->numA;
                    int numB = ((bytecode::Instruction2Number *) curFrame->curInstruction())->numB;
                    switch (curFrame->curInstruction()->opCode) {
                        case bytecode::OpCode::FuncCall:
                            runFuncCall(numA, numB);
                            break;
                        case bytecode::OpCode::NativeFuncCall:
                            runNativeFuncCall(numA, numB);
                            break;
                    }
                } else if (curFrame->curInstruction()->introductionType() == bytecode::InstructionType::With1Number) {
                    int num = ((bytecode::Instruction1Number *) curFrame->curInstruction())->num;
                    switch (curFrame->curInstruction()->opCode) {
                        case bytecode::OpCode::PushIntConst:
                            runPushIntConst(num);
                            break;
                        case bytecode::OpCode::PushCharConst:
                            runPushCharConst(num);
                            break;
                        case bytecode::OpCode::PushStringConst:
                            runPushStringConst(num);
                            break;
                        case bytecode::OpCode::PushGlobalVar:
                            runPushGlobalVar(num);
                            break;
                        case bytecode::OpCode::PushLocalVar:
                            runPushLocalVar(num);
                            break;
                        case bytecode::OpCode::SetGlobalVar:
                            runSetGlobalVar(num);
                            break;
                        case bytecode::OpCode::SetLocalVar:
                            runSetLocalVar(num);
                            break;
                        case bytecode::OpCode::GotoIfTrue:
                            runGotoIfTrue(num);
                            break;
                        case bytecode::OpCode::GotoIfFalse:
                            runGotoIfFalse(num);
                            break;
                        case bytecode::OpCode::Goto:
                            runGoto(num);
                            break;
                        case bytecode::OpCode::MakeArray:
                            runMakeArray(num);
                            break;
                    }
                } else {
                    switch (curFrame->curInstruction()->opCode) {
                        case bytecode::OpCode::Return:
                            runReturn();
                            break;
                        case bytecode::OpCode::ReturnNull:
                            runReturnNull();
                            break;
                        case bytecode::OpCode::PushTrue:
                            runPushTrue();
                            break;
                        case bytecode::OpCode::PushFalse:
                            runPushFalse();
                            break;
                        case bytecode::OpCode::Pop:
                            runPop();
                            break;
                        case bytecode::OpCode::SetArrayIndex:
                            runSetArrayIndex();
                            break;
                        case bytecode::OpCode::GetArrayIndex:
                            runGetArrayIndex();
                            break;
                        case bytecode::OpCode::Minus:
                            runMinus();
                            break;
                        case bytecode::OpCode::Add:
                            runAdd();
                            break;
                        case bytecode::OpCode::Mul:
                            runMul();
                            break;
                        case bytecode::OpCode::Div:
                            runDiv();
                            break;
                        case bytecode::OpCode::Mod:
                            runMod();
                            break;
                        case bytecode::OpCode::LessThan:
                            runLessThan();
                            break;
                        case bytecode::OpCode::LessEqual:
                            runLessEqual();
                            break;
                        case bytecode::OpCode::GreaterThan:
                            runGreaterThan();
                            break;
                        case bytecode::OpCode::GreaterEqual:
                            runGreaterEqual();
                            break;
                        case bytecode::OpCode::Equal:
                            runEqual();
                            break;
                        case bytecode::OpCode::NotEqual:
                            runNotEqual();
                            break;
                        case bytecode::OpCode::And:
                            runAnd();
                            break;
                        case bytecode::OpCode::Or:
                            runOr();
                            break;
                        case bytecode::OpCode::BAnd:
                            runBAnd();
                            break;
                        case bytecode::OpCode::BOr:
                            runBOr();
                            break;
                        case bytecode::OpCode::BXor:
                            runBXor();
                            break;
                        case bytecode::OpCode::LMove:
                            runLMove();
                            break;
                        case bytecode::OpCode::RMove:
                            runRMove();
                            break;
                        case bytecode::OpCode::PreMinus:
                            runPreMinus();
                            break;
                        case bytecode::OpCode::Not:
                            runNot();
                            break;
                        case bytecode::OpCode::BNot:
                            runBNot();
                            break;
                        case bytecode::OpCode::TypeToInt:
                            runTypeToInt();
                            break;
                        case bytecode::OpCode::TypeToString:
                            runTypeToString();
                            break;
                        case bytecode::OpCode::TypeToChar:
                            runTypeToChar();
                            break;
                        case bytecode::OpCode::TypeToBool:
                            runTypeToBool();
                            break;
                    }
                }
                if (frames.size() > 0) {
                    curFrame->setPc(curFrame->getPc() + 1);
                }
            }
        }
    }
}