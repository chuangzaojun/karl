#ifndef KARL_FRAME_HPP
#define KARL_FRAME_HPP

#include "object.hpp"
#include "../bytecode/bytecode.hpp"

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

            Object *push(Object *object);
            Object *pop();
            int size();

            void setVar(int index, Object *object);
            Object *getVar(int index);

            bytecode::FuncInfo *getFuncInfo();
            int getPc();
            void setPc(int newPc);

            Frame(bytecode::FuncInfo *funcInfo);
        };

    }
}

#endif //KARL_FRAME_HPP
