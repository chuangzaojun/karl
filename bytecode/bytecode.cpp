#include "bytecode.hpp"

namespace karl {
    namespace bytecode {
        Bytecode::~Bytecode() {
            for (FuncInfo *funcInfo: funcInfos) {
                delete funcInfo;
            }
        }

        std::string Bytecode::toString() {
            std::string st;
            for (int i = 0; i < funcInfos.size(); i++) {
                st += "func " + std::to_string(i) + ":\n" + funcInfos[i]->toString() + "\n";
            }
            st += "int consts:\n";
            for (int i = 0; i < intConsts.size(); i++) {
                st += "[" + std::to_string(i) + "]" + std::to_string(intConsts[i]) + "\n";
            }
            st += "char consts:\n";
            for (int i = 0; i < charConsts.size(); i++) {
                st += "[" + std::to_string(i) + "]" + charConsts[i] + "\n";
            }
            st += "string consts:\n";
            for (int i = 0; i < stringConsts.size(); i++) {
                st += "[" + std::to_string(i) + "]" + stringConsts[i] + "\n";
            }
            return st;
        }
    }
}