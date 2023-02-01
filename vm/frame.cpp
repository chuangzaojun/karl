#include "frame.hpp"

namespace karl {
    namespace vm {

        Frame::Frame(bytecode::FuncInfo *funcInfo) {
            this->funcInfo = funcInfo;
            stack.resize(funcInfo->maxStackSize + 10);
            vars.resize(funcInfo->maxLocalVarNum + 10);
            stackSize = 0;
            pc = 0;
        }

        Object *Frame::getVar(int index) {
            return vars[index];
        }

        Object *Frame::setVar(int index, Object *object) {
            vars[index] = object;
            return object;
        }

        Object *Frame::push(Object *object) {
            stack[stackSize] = object;
            stackSize++;
            return object;
        }

        Object *Frame::pop() {
            stack[stackSize] = nullptr;
            stackSize--;
            return stack[stackSize];
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

        bytecode::Instruction *Frame::curInstruction() {
            return funcInfo->instructions[pc];
        }
    }
}