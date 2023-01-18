#include "heap.hpp"

namespace karl {
    namespace vm {

        Object *Heap::defineNewObject(Object *object) {
            objects.push_back(object);
            return object;
        }
    }
}