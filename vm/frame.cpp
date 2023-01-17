#include "frame.hpp"

namespace karl {
    namespace vm {

        Frame::Frame(int maxStackSize, int maxVarNum) {
            stack.resize(maxStackSize);
            vars.resize(maxVarNum);
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

        int Frame::push(Object *object) {
            stack[stackSize] = object;
            int temp = stackSize;
            stackSize++;
            return temp;
        }

        void Frame::setVar(int index, Object *object) {
            vars[index] = object;
        }

        Object *Frame::getVar(int index) {
            return vars[index];
        }
    }
}