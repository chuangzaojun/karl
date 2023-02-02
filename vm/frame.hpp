#ifndef KARL_FRAME_HPP
#define KARL_FRAME_HPP

#include "../bytecode/func_info.hpp"
#include "object.hpp"
#include <vector>

namespace karl {
    namespace vm {

        class Frame {
        private:
            std::vector<Object *> stack;
            std::vector<Object *> vars;
            int stackSize;

            int pc;

            bytecode::FuncInfo *funcInfo;

        public:
            Object *getVar(int index);
            Object *setVar(int index, Object *object);
            Object *push(Object *object);
            Object *pop();

            bytecode::FuncInfo *getFuncInfo();
            int getPc();
            void setPc(int newPc);
            bytecode::Instruction *curInstruction();

            void markObjects();

            Frame(bytecode::FuncInfo *funcInfo);
        };

    }
}

#endif //KARL_FRAME_HPP
