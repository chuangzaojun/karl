#ifndef KARL_FUNC_INFO_HPP
#define KARL_FUNC_INFO_HPP

#include "introduction.hpp"
#include <vector>

namespace karl {
    namespace bytecode {
        struct FuncInfo {
            int maxStackSize;
            int maxLocalVarNum;
            std::vector<Introduction *> introductions;

            ~FuncInfo();
        };
    }
}

#endif //KARL_FUNC_INFO_HPP
