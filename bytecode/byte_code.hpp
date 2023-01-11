#ifndef KARL_BYTE_CODE_HPP
#define KARL_BYTE_CODE_HPP

#include "func_info.hpp"
#include <vector>
#include <string>

namespace karl {
    namespace bytecode {
        struct ByteCode {
            int maxGlobalVarNum;

            std::vector<FuncInfo *> funcInfos;

            std::vector<int> intConsts;
            std::vector<char> charConsts;
            std::vector<std::string> stringConsts;

            ~ByteCode();
        };
    }

}

#endif //KARL_BYTE_CODE_HPP
