#include "vm.hpp"
#include "native_func.hpp"

namespace karl {
    namespace vm {

        VM::VM(bytecode::Bytecode *bytecode, Heap *heap) {
            this->bytecode = bytecode;
            this->heap = heap;
            globalVars.resize(bytecode->maxGlobalVarNum + 10);
        }

        void VM::pushFrame(int funcIndex) {
            curFrame = new Frame(bytecode->funcInfos[funcIndex]);
            stack.push_back(curFrame);
        }

        void VM::popFrame() {
            delete curFrame;
            stack.pop_back();
            std::list<Frame *>::iterator it = stack.end();
            it--;
            curFrame = *it;
        }

        void VM::run() {
            globalVars.resize(bytecode->maxGlobalVarNum);
            pushFrame(0);
            while (stack.size() > 0) {
                if (curFrame->getFuncInfo()->introductions[curFrame->getPc()]->introductionType() ==
                    bytecode::InstructionType::With2Number) {
                    int numA = ((bytecode::Instruction2Number *) curFrame->getFuncInfo()
                            ->introductions[curFrame->getPc()])->numA;
                    int numB = ((bytecode::Instruction2Number *) curFrame->getFuncInfo()
                            ->introductions[curFrame->getPc()])->numB;
                    switch (curFrame->getFuncInfo()->introductions[curFrame->getPc()]->opCode) {
                        case bytecode::OpCode::FuncCall:
                            runFuncCall(numA, numB);
                            break;
                        case bytecode::OpCode::NativeFuncCall:
                            runNativeFuncCall(numA, numB);
                            break;
                    }
                } else if (curFrame->getFuncInfo()->introductions[curFrame->getPc()]->introductionType() ==
                           bytecode::InstructionType::With1Number) {
                    int num = ((bytecode::Instruction1Number *) curFrame->getFuncInfo()
                            ->introductions[curFrame->getPc()])->num;
                    switch (curFrame->getFuncInfo()->introductions[curFrame->getPc()]->opCode) {
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
                    switch (curFrame->getFuncInfo()->introductions[curFrame->getPc()]->opCode) {
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
                curFrame->setPc(curFrame->getPc() + 1);
            }
        }

        void VM::runFuncCall(int argumentNum, int funcIndex) {
            std::vector<Object *> arguments(argumentNum);
            for (int i = 0; i < argumentNum; i++) {
                arguments[i] = curFrame->pop();
            }
            pushFrame(funcIndex);
            for (int i = 0; i < argumentNum; i++) {
                curFrame->setVar(i, arguments[i]);
            }
            curFrame->setPc(-1);
        }

        void VM::runNativeFuncCall(int argumentNum, int funcIndex) {
            std::vector<Object *> arguments(argumentNum);
            for (int i = 0; i < argumentNum; i++) {
                arguments[i] = curFrame->pop();
            }
            switch (funcIndex) {
                case 0:
                    NativeFunc::print(arguments);
                    break;
            }
        }

        void VM::runPushIntConst(int index) {
            heap->defineNewObject(curFrame->push(new IntObject(bytecode->intConsts[index])));
        }

        void VM::runPushCharConst(int index) {
            heap->defineNewObject(curFrame->push(new CharObject(bytecode->charConsts[index])));
        }

        void VM::runPushStringConst(int index) {
            heap->defineNewObject(curFrame->push(new StringObject(bytecode->stringConsts[index])));
        }

        void VM::runPushGlobalVar(int index) {
            curFrame->push(globalVars[index]);
        }

        void VM::runPushLocalVar(int index) {
            curFrame->push(curFrame->getVar(index));
        }

        void VM::runSetGlobalVar(int index) {
            globalVars[index] = curFrame->pop();
        }

        void VM::runSetLocalVar(int index) {
            curFrame->setVar(index, curFrame->pop());
        }

        void VM::runGotoIfTrue(int newPc) {
            if (((BoolObject *) curFrame->pop())->value == true) {
                curFrame->setPc(newPc - 1);
            }
        }

        void VM::runGotoIfFalse(int newPc) {
            if (((BoolObject *) curFrame->pop())->value == false) {
                curFrame->setPc(newPc - 1);
            }
        }

        void VM::runGoto(int newPc) {
            curFrame->setPc(newPc - 1);
        }

        void VM::runMakeArray(int size) {
            ArrayObject *arrayObject = new ArrayObject(size);
            for (int i = 0; i < size; i++) {
                arrayObject->value[i] = curFrame->pop();
            }
            heap->defineNewObject(curFrame->push(arrayObject));
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
            heap->defineNewObject(curFrame->push(new BoolObject(true)));
        }

        void VM::runPushFalse() {
            heap->defineNewObject(curFrame->push(new BoolObject(false)));
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
            Object *array = (ArrayObject *) curFrame->pop();
            switch (array->type()) {
                case SingleObjectType::Array: {
                    curFrame->push(((ArrayObject *) array)->value[index]);
                    break;
                }
                case SingleObjectType::String: {
                    curFrame->push(heap->defineNewObject(new CharObject(((StringObject *) array)->value[index])));
                    break;
                }
            }
        }

        void VM::runMinus() {
            int b = ((IntObject *) curFrame->pop())->value;
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(a - b)));
        }

        void VM::runAdd() {
            Object *b = curFrame->pop();
            Object *a = curFrame->pop();
            switch (a->type()) {
                case SingleObjectType::Int: {
                    int numA = ((IntObject *) a)->value;
                    int numB = ((IntObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new IntObject(numA + numB)));
                    break;
                }
                case SingleObjectType::String: {
                    std::string numA = ((StringObject *) a)->value;
                    std::string numB = ((StringObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new StringObject(numA + numB)));
                    break;
                }
            }
        }

        void VM::runMul() {
            int b = ((IntObject *) curFrame->pop())->value;
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(a * b)));
        }

        void VM::runDiv() {
            int b = ((IntObject *) curFrame->pop())->value;
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(a / b)));
        }

        void VM::runMod() {
            int b = ((IntObject *) curFrame->pop())->value;
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(a % b)));
        }

        void VM::runLessThan() {
            Object *b = curFrame->pop();
            Object *a = curFrame->pop();
            switch (a->type()) {
                case SingleObjectType::Int: {
                    int numA = ((IntObject *) a)->value;
                    int numB = ((IntObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA < numB)));
                    break;
                }
                case SingleObjectType::Char: {
                    char numA = ((CharObject *) a)->value;
                    char numB = ((CharObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA < numB)));
                    break;
                }
                case SingleObjectType::Bool: {
                    bool numA = ((BoolObject *) a)->value;
                    bool numB = ((BoolObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA < numB)));
                    break;
                }
            }
        }

        void VM::runLessEqual() {
            Object *b = curFrame->pop();
            Object *a = curFrame->pop();
            switch (a->type()) {
                case SingleObjectType::Int: {
                    int numA = ((IntObject *) a)->value;
                    int numB = ((IntObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA <= numB)));
                    break;
                }
                case SingleObjectType::Char: {
                    char numA = ((CharObject *) a)->value;
                    char numB = ((CharObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA <= numB)));
                    break;
                }
                case SingleObjectType::Bool: {
                    bool numA = ((BoolObject *) a)->value;
                    bool numB = ((BoolObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA <= numB)));
                    break;
                }
            }
        }

        void VM::runGreaterThan() {
            Object *b = curFrame->pop();
            Object *a = curFrame->pop();
            switch (a->type()) {
                case SingleObjectType::Int: {
                    int numA = ((IntObject *) a)->value;
                    int numB = ((IntObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA > numB)));
                    break;
                }
                case SingleObjectType::Char: {
                    char numA = ((CharObject *) a)->value;
                    char numB = ((CharObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA > numB)));
                    break;
                }
                case SingleObjectType::Bool: {
                    bool numA = ((BoolObject *) a)->value;
                    bool numB = ((BoolObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA > numB)));
                    break;
                }
            }
        }

        void VM::runGreaterEqual() {
            Object *b = curFrame->pop();
            Object *a = curFrame->pop();
            switch (a->type()) {
                case SingleObjectType::Int: {
                    int numA = ((IntObject *) a)->value;
                    int numB = ((IntObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA >= numB)));
                    break;
                }
                case SingleObjectType::Char: {
                    char numA = ((CharObject *) a)->value;
                    char numB = ((CharObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA >= numB)));
                    break;
                }
                case SingleObjectType::Bool: {
                    bool numA = ((BoolObject *) a)->value;
                    bool numB = ((BoolObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA >= numB)));
                    break;
                }
            }
        }

        void VM::runEqual() {
            Object *b = curFrame->pop();
            Object *a = curFrame->pop();
            switch (a->type()) {
                case SingleObjectType::Int: {
                    int numA = ((IntObject *) a)->value;
                    int numB = ((IntObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA == numB)));
                    break;
                }
                case SingleObjectType::Char: {
                    char numA = ((CharObject *) a)->value;
                    char numB = ((CharObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA == numB)));
                    break;
                }
                case SingleObjectType::Bool: {
                    bool numA = ((BoolObject *) a)->value;
                    bool numB = ((BoolObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA == numB)));
                    break;
                }
                case SingleObjectType::String: {
                    std::string numA = ((StringObject *) a)->value;
                    std::string numB = ((StringObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA == numB)));
                    break;
                }
            }
        }

        void VM::runNotEqual() {
            Object *b = curFrame->pop();
            Object *a = curFrame->pop();
            switch (a->type()) {
                case SingleObjectType::Int: {
                    int numA = ((IntObject *) a)->value;
                    int numB = ((IntObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA != numB)));
                    break;
                }
                case SingleObjectType::Char: {
                    char numA = ((CharObject *) a)->value;
                    char numB = ((CharObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA != numB)));
                    break;
                }
                case SingleObjectType::Bool: {
                    bool numA = ((BoolObject *) a)->value;
                    bool numB = ((BoolObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA != numB)));
                    break;
                }
                case SingleObjectType::String: {
                    std::string numA = ((StringObject *) a)->value;
                    std::string numB = ((StringObject *) b)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(numA != numB)));
                    break;
                }
            }
        }

        void VM::runAnd() {
            bool b = ((BoolObject *) curFrame->pop())->value;
            bool a = ((BoolObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new BoolObject(a && b)));
        }

        void VM::runOr() {
            bool b = ((BoolObject *) curFrame->pop())->value;
            bool a = ((BoolObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new BoolObject(a || b)));
        }

        void VM::runBAnd() {
            int b = ((IntObject *) curFrame->pop())->value;
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(a & b)));
        }

        void VM::runBOr() {
            int b = ((IntObject *) curFrame->pop())->value;
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(a | b)));
        }

        void VM::runBXor() {
            int b = ((IntObject *) curFrame->pop())->value;
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(a ^ b)));
        }

        void VM::runLMove() {
            int b = ((IntObject *) curFrame->pop())->value;
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(a << b)));
        }

        void VM::runRMove() {
            int b = ((IntObject *) curFrame->pop())->value;
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(a >> b)));
        }

        void VM::runPreMinus() {
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(-a)));
        }

        void VM::runNot() {
            bool a = ((BoolObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new BoolObject(!a)));
        }

        void VM::runBNot() {
            int a = ((IntObject *) curFrame->pop())->value;
            curFrame->push(heap->defineNewObject(new IntObject(~a)));
        }

        void VM::runTypeToInt() {
            Object *object = curFrame->pop();
            switch (object->type()) {
                case SingleObjectType::Int: {
                    curFrame->push(object);
                    break;
                }
                case SingleObjectType::Char: {
                    char ch = ((CharObject *) object)->value;
                    curFrame->push(heap->defineNewObject(new IntObject((int) ch)));
                    break;
                }
                case SingleObjectType::String: {
                    std::string st = ((StringObject *) object)->value;
                    curFrame->push(heap->defineNewObject(new IntObject(std::stoi(st))));
                    break;
                }
                case SingleObjectType::Bool: {
                    bool num = ((BoolObject *) object)->value;
                    curFrame->push(heap->defineNewObject(new IntObject((int) num)));
                    break;
                }
            }
        }

        void VM::runTypeToString() {
            Object *object = curFrame->pop();
            switch (object->type()) {
                case SingleObjectType::String: {
                    curFrame->push(object);
                    break;
                }
                case SingleObjectType::Char: {
                    char ch = ((CharObject *) object)->value;
                    std::string st;
                    st[0] = ch;
                    curFrame->push(heap->defineNewObject(new StringObject(st)));
                    break;
                }
                case SingleObjectType::Int: {
                    int num = ((IntObject *) object)->value;
                    curFrame->push(heap->defineNewObject(new StringObject(std::to_string(num))));
                    break;
                }
                case SingleObjectType::Bool: {
                    bool num = ((BoolObject *) object)->value;
                    if (num == true) {
                        curFrame->push(heap->defineNewObject(new StringObject("true")));
                    } else {
                        curFrame->push(heap->defineNewObject(new StringObject("false")));
                    }
                    break;
                }
            }
        }

        void VM::runTypeToChar() {
            Object *object = curFrame->pop();
            switch (object->type()) {
                case SingleObjectType::Char: {
                    curFrame->push(object);
                    break;
                }
                case SingleObjectType::Int: {
                    int num = ((IntObject *) object)->value;
                    curFrame->push(heap->defineNewObject(new CharObject((char) num)));
                    break;
                }
            }
        }

        void VM::runTypeToBool() {
            Object *object = curFrame->pop();
            switch (object->type()) {
                case SingleObjectType::Bool: {
                    curFrame->push(object);
                    break;
                }
                case SingleObjectType::Int: {
                    int num = ((IntObject *) object)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject((bool) num)));
                    break;
                }
                case SingleObjectType::String: {
                    std::string st = ((StringObject *) object)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject(st == "true")));
                    break;
                }
                case SingleObjectType::Char: {
                    char ch = ((CharObject *) object)->value;
                    curFrame->push(heap->defineNewObject(new BoolObject((bool) ch)));
                    break;
                }
            }
        }
    }
}