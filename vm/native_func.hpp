#ifndef KARL_NATIVE_FUNC_HPP
#define KARL_NATIVE_FUNC_HPP

#include "object.hpp"
#include <vector>

namespace karl {
    namespace vm {
        class NativeFunc {
        public:
            static void print(std::vector<Object *> &arguments);
        };
    }
}

#endif //KARL_NATIVE_FUNC_HPP
