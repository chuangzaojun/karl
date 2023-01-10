#include "func_table.hpp"
#include "../error/error.hpp"

namespace karl::compiler {
    void FuncTable::set(std::string func, FuncDefStmt *stmt, int line, int column) {
        if (funcStmts.count(func) > 0) {
            TypeError::funcHasDefError(func, line, column);
        }
        funcStmts[func] = stmt;
    }

    FuncDefStmt *FuncTable::get(std::string func, int line, int column) {
        if (funcStmts.count(func) == 0) {
            TypeError::funcNotFoundError(func, line, column);
        }
        return funcStmts[func];
    }
} // karl