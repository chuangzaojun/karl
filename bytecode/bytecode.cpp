#include "bytecode.hpp"

namespace karl {
    namespace bytecode {
        ByteCode::~ByteCode() {
            for (FuncInfo *funcInfo: funcInfos) {
                delete funcInfo;
            }
        }
    }
}