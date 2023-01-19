#include "frame.hpp"

namespace karl {
    namespace vm {

        Frame::Frame(bytecode::FuncInfo *funcInfo) {
            this->funcInfo = funcInfo;
            stack.resize(funcInfo->maxStackSize + 10);
            vars.resize(funcInfo->maxLocalVarNum + 10);
            this->stackSize = 0;
            this->pc = 0;
        }

        int Frame::size() {
            return stackSize;
        }

        Object *Frame::pop() {
            stackSize--;
            Object *temp = stack[stackSize];
            stack[stackSize] = nullptr;
            return temp;
        }

        Object *Frame::push(Object *object) {
            stack[stackSize] = object;
            stackSize++;
            return object;
        }

        void Frame::setVar(int index, Object *object) {
            vars[index] = object;
        }

        Object *Frame::getVar(int index) {
            return vars[index];
        }

        bytecode::FuncInfo *Frame::getFuncInfo() {
            return funcInfo;
        }

        int Frame::getPc() {
            return pc;
        }

        void Frame::setPc(int newPc) {
            pc = newPc;
        }
    }
}