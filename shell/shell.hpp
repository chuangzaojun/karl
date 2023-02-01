#ifndef KARL_SHELL_HPP
#define KARL_SHELL_HPP

#include <vector>
#include <string>

namespace karl {
    namespace shell {
        std::string read(std::string fileName);

        void run(std::vector<std::string> &args);
    }
}

#endif //KARL_SHELL_HPP
