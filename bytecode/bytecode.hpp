#ifndef KARL_BYTECODE_HPP
#define KARL_BYTECODE_HPP

#include "func_info.hpp"
#include <vector>
#include <string>

namespace karl {
    namespace bytecode {
        struct Bytecode {
            int maxGlobalVarNum;

            std::vector<FuncInfo *> funcInfos;

            std::vector<int> intConsts;
            std::vector<char> charConsts;
            std::vector<std::string> stringConsts;

            std::string toString();
            ~Bytecode();
        };
    }

}

#endif //KARL_BYTECODE_HPP
