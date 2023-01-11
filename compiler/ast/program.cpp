#include "program.hpp"

namespace karl {
    namespace compiler {
        Program::~Program() {
            for (Stmt *i: stmts) {
                delete i;
            }
            delete varTable;
            delete funcTable;
        }
    }
}