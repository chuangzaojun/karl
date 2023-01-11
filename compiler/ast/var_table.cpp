#include "var_table.hpp"
#include "../error/error.hpp"

namespace karl {
    namespace compiler {
        VarTable::VarTable(VarTable *outer) {
            this->outer = outer;
        }

        void VarTable::set(std::string var, ObjectType *type, int line, int column) {
            if (varTypes.count(var) > 0) {
                TypeError::varHasDefError(var, line, column);
            }
            varTypes[var] = type;
            varIndexes[var] = localVarNum();
        }

        ObjectType *VarTable::getType(std::string var, int line, int column) {
            if (varTypes.count(var) == 0) {
                if (outer == nullptr) {
                    TypeError::varNotFoundError(var, line, column);
                }
                return outer->getType(var, line, column);
            }
            return varTypes[var]->copy();
        }

        bool VarTable::isLocalVar(std::string var) {
            if (outer == nullptr) {
                return false;
            }
            return outer->isLocalVar(var);
        }

        int VarTable::localVarNum() {
            if (outer == nullptr) {
                return 0;
            }
            return outer->localVarNum() + varIndexes.size();
        }

        int VarTable::getIndex(std::string var) {
            if (varIndexes.count(var) != 0) {
                return varIndexes[var];
            }
            return outer->getIndex(var);
        }

        int VarTable::globalVarNum() {
            if (outer == nullptr) {
                return varIndexes.size();
            }
            return outer->globalVarNum();
        }
    }
}