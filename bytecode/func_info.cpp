#include "func_info.hpp"

namespace karl {
    namespace bytecode {
        FuncInfo::~FuncInfo() {
            for (Instruction *instruction: instructions) {
                delete instruction;
            }
        }

        std::string FuncInfo::toString() {
            std::string st;
            for (int i = 0; i < instructions.size(); i++) {
                st += "[" + std::to_string(i) + "] " + instructions[i]->toString() + "\n";
            }
            return st;
        }

        FuncInfo::FuncInfo() {
            maxLocalVarNum = 0;
            maxStackSize = 0;
        }
    }
}