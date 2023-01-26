#include "func_info.hpp"

namespace karl {
    namespace bytecode {
        FuncInfo::~FuncInfo() {
            for (Instruction *introduction: instructions) {
                delete introduction;
            }
        }

        std::string FuncInfo::toString() {
            std::string st;
            for (Instruction *instruction: instructions) {
                st += instruction->toString() + "\n";
            }
            return st;
        }
    }
}