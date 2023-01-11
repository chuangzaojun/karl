#include "func_info.hpp"

namespace karl {
    namespace bytecode {
        FuncInfo::~FuncInfo() {
            for (Introduction *introduction: introductions) {
                delete introduction;
            }
        }
    }
}