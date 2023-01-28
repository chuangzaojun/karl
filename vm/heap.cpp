#include "heap.hpp"

namespace karl {
    namespace vm {

        void Heap::define(Object *object) {
            objects.push_back(object);
        }

        Heap::~Heap() {
            for (Object *object: objects) {
                delete object;
            }
        }
    }
}