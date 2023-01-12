#include "bytecode.hpp"

namespace karl {
    namespace bytecode {
        Bytecode::~Bytecode() {
            for (FuncInfo *funcInfo: funcInfos) {
                delete funcInfo;
            }
        }
    }
}