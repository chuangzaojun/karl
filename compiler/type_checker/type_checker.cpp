#include "type_checker.hpp"

namespace karl {
    TypeChecker::TypeChecker(Program *program) {
        this->program = program;
        this->curBlock = nullptr;
        this->curLoopBlock = nullptr;
    }

    void TypeChecker::checkProgram() {
        for (Stmt *)
    }
} // karl