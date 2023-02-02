#ifndef KARL_HEAP_HPP
#define KARL_HEAP_HPP

#include "object.hpp"
#include <vector>

namespace karl {
    namespace vm {
        class Heap {
        private:
            std::vector<Object *> objects;
            int numDefObject;

        public:

            Heap();
            Object *define(Object *object);
            int getNumDefObject();
            void markObjects();
            void freeObjects();
            bool hasGreyObject();
            ~Heap();
        };
    }
}

#endif //KARL_HEAP_HPP
