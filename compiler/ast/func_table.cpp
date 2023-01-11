#include "func_table.hpp"
#include "../error/error.hpp"

namespace karl {
    namespace compiler {
        void FuncTable::set(std::string func, FuncDefStmt *stmt, int line, int column) {
            if (funcStmts.count(func) > 0) {
                TypeError::funcHasDefError(func, line, column);
            }
            if (func != "main") {
                funcIndexes[func] = funcNum();
            }
            funcStmts[func] = stmt;
        }

        FuncDefStmt *FuncTable::getStmt(std::string func, int line, int column) {
            if (funcStmts.count(func) == 0) {
                TypeError::funcNotFoundError(func, line, column);
            }
            return funcStmts[func];
        }

        FuncTable::FuncTable() {
            funcIndexes["main"] = 0;
        }

        int FuncTable::getIndex(std::string func) {
            return funcIndexes[func];
        }

        int FuncTable::funcNum() {
            return funcIndexes.size();
        }
    }
}