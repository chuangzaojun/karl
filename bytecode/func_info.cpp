#include "func_info.hpp"

namespace karl {
    namespace bytecode {
        FuncInfo::~FuncInfo() {
            for (Instruction *introduction: introductions) {
                delete introduction;
            }
        }
    }
}