#include "byte_code.hpp"

namespace karl {
    namespace bytecode {
        ByteCode::~ByteCode() {
            for (FuncInfo *funcInfo: funcInfos) {
                delete funcInfo;
            }
        }
    }
}