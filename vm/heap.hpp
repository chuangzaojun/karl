#ifndef KARL_HEAP_HPP
#define KARL_HEAP_HPP

#include "object.hpp"
#include <list>

namespace karl {
    namespace vm {
        class Heap {
        private:
            std::list<Object *> objects;

        public:
            Object *defineNewObject(Object *object);
        };
    }
}

#endif //KARL_HEAP_HPP
