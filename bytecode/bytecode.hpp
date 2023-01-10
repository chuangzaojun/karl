#ifndef KARL_BYTECODE_HPP
#define KARL_BYTECODE_HPP

#include "func_info.hpp"
#include <vector>
#include <string>

namespace karl::bytecode {

    struct ByteCode {
        std::vector<FuncInfo *> funcInfos;

        std::vector<int> intConsts;
        std::vector<char> charConsts;
        std::vector<std::string> stringConsts;
    };

} // karl

#endif //KARL_BYTECODE_HPP
