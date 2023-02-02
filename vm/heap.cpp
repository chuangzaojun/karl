#include "heap.hpp"

namespace karl {
    namespace vm {

        Object *Heap::define(Object *object) {
            objects.push_back(object);
            numDefObject++;
            return object;
        }

        Heap::~Heap() {
            for (Object *object: objects) {
                delete object;
            }
        }

        Heap::Heap() {
            numDefObject = 0;
        }

        int Heap::getNumDefObject() {
            return numDefObject;
        }

        void Heap::freeObjects() {
//            int s = 0;
            for (std::vector<Object *>::iterator it = objects.begin(); it != objects.end(); it++) {
                if ((*it)->color == ObjectColor::White) {
                    delete *it;
//                    s++;
                    objects.erase(it);
                    it--;
                } else {
                    (*it)->color = ObjectColor::White;
                }
            }
//            printf("delete %d objects\n", s);
            numDefObject = 0;
        }

        bool Heap::hasGreyObject() {
            for (Object *object: objects) {
                if (object->color == ObjectColor::Grey) {
                    return true;
                }
            }
            return false;
        }

        void Heap::markObjects() {
            for (Object *object: objects) {
                if (object->color == ObjectColor::Grey) {
                    object->mark();
                }
            }
        }
    }
}