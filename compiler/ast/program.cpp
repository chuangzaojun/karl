#include "program.hpp"

namespace karl {
    Program::~Program() {
        for (Stmt *i: stmts) {
            delete i;
        }
    }
} // karl