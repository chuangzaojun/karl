#ifndef KARL_FUNC_INFO_HPP
#define KARL_FUNC_INFO_HPP

#include "introduction.hpp"
#include <vector>

namespace karl::bytecode {
    struct FuncInfo {
        std::vector<Introduction *> introductions;
    };
} // karl

#endif //KARL_FUNC_INFO_HPP
