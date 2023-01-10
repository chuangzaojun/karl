#ifndef KARL_BYTE_CODE_HPP
#define KARL_BYTE_CODE_HPP

#include <vector>
#include <string>

namespace karl::bytecode {

    struct ByteCode {

        std::vector<int> intConsts;
        std::vector<char> charConsts;
        std::vector<std::string> stringConsts;

    };

} // karl

#endif //KARL_BYTE_CODE_HPP
