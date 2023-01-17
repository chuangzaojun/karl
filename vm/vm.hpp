#ifndef KARL_VM_HPP
#define KARL_VM_HPP

#include "frame.hpp"
#include "heap.hpp"
#include "../bytecode/bytecode.hpp"
#include <list>

namespace karl {
    namespace vm {
        class VM {
        private:
            bytecode::Bytecode *bytecode;
            bytecode::FuncInfo *curFuncInfo;
            std::list<Frame *> stack;
            Frame *curFrame;

            Heap *heap;

            void pushFrame(int maxStackSize, int maxVarNum);
            void popFrame();

        public:
            VM(bytecode::Bytecode *bytecode, Heap *heap);
            void run();
        };
    }

} // karl

#endif //KARL_VM_HPP
