#ifndef KARL_FUNC_INFO_HPP
#define KARL_FUNC_INFO_HPP

#include "instruction.hpp"
#include <vector>

namespace karl {
    namespace bytecode {
        struct FuncInfo {
            int maxStackSize;
            int maxLocalVarNum;
            std::vector<Instruction *> instructions;

            std::string toString();

            ~FuncInfo();
        };
    }
}

#endif //KARL_FUNC_INFO_HPP
