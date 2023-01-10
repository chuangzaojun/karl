#include "program.hpp"

namespace karl::compiler {
    Program::~Program() {
        for (Stmt *i: stmts) {
            delete i;
        }
        delete varTable;
        delete funcTable;
    }
} // karl