#include "frame.hpp"

namespace karl {
    namespace vm {

        Frame::Frame(bytecode::FuncInfo *funcInfo) {
            stack.resize(funcInfo->maxStackSize);
            vars.resize(funcInfo->maxLocalVarNum);
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
            int temp = stackSize;
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