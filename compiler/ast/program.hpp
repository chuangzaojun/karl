#ifndef KARL_PROGRAM_HPP
#define KARL_PROGRAM_HPP

#include "stmt.hpp"
#include "func_table.hpp"
#include <vector>

namespace karl {

    struct Program {
        std::vector<Stmt *> stmts;
        VarTable *varTable;
        FuncTable *funcTable;

        ~Program();
    };

} // karl

#endif //KARL_PROGRAM_HPP
