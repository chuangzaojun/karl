#ifndef KARL_FRAME_HPP
#define KARL_FRAME_HPP

#include "object.hpp"

namespace karl {
    namespace vm {

        class Frame {
        private:
            std::vector<Object *> stack;
            std::vector<Object *> vars;
            int stackSize;

        public:

            int push(Object *object);
            Object *pop();
            int size();

            void setVar(int index, Object *object);
            Object *getVar(int index);

            Frame(int maxStackSize, int maxVarNum);
        };

    }
}

#endif //KARL_FRAME_HPP
