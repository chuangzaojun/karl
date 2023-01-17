#include "vm.hpp"

namespace karl {
    namespace vm {

        void VM::pushFrame(int maxStackSize, int maxVarNum) {
            curFrame = new Frame(maxStackSize, maxVarNum);
            stack.push_back(curFrame);
        }

        void VM::popFrame() {
            delete curFrame;
            stack.pop_back();
            std::list<Frame *>::iterator it = stack.end();
            it--;
            curFrame = *it;
        }

        VM::VM(bytecode::Bytecode *bytecode, Heap *heap) {
            this->bytecode = bytecode;
            this->heap = heap;
        }
    }
} // karl