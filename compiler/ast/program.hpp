#ifndef KARL_PROGRAM_HPP
#define KARL_PROGRAM_HPP

#include "stmt.hpp"
#include <vector>

namespace karl {

    struct Program {
        std::vector<Stmt *> stmts;

        ~Program();
    };

} // karl

#endif //KARL_PROGRAM_HPP
