#include "heap.hpp"

namespace karl {
    namespace vm {

        Object *Heap::define(Object *object) {
            objects.push_back(object);
            return object;
        }

        Heap::~Heap() {
            for (Object *object: objects) {
                delete object;
            }
        }
    }
}