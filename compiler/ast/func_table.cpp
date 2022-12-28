#include "func_table.hpp"
#include "../../error/error.hpp"

namespace karl {
    void FuncTable::set(std::string func, FuncDefStmt *stmt, int line, int column) {
        if (funcStmts.count(func)) {
            funcHasDefError(func, line, column);
        }
        funcStmts[func] = stmt;
    }

    FuncDefStmt *FuncTable::get(std::string func, int line, int column) {
        if (!funcStmts.count(func)) {
            funcNotFoundError(func, line, column);
        }
        return funcStmts[func];
    }

    FuncTable::~FuncTable() {

    }
} // karl