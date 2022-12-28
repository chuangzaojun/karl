#include "var_table.hpp"
#include "../../error/error.hpp"

namespace karl {
    VarTable::VarTable(VarTable *outer) {
        this->outer = outer;
    }

    void VarTable::set(std::string var, ObjectType *type, int line, int column) {
        if (!varTypes.count(var)) {
            varHasDefError(var, line, column);
        }
        varTypes[var] = type;
    }

    ObjectType *VarTable::get(std::string var, int line, int column) {
        if (!varTypes.count(var)) {
            if (outer == nullptr) {
                varNotFoundError(var, line, column);
            }
            return outer->get(var, line, column);
        }
        return varTypes[var]->copy();
    }

    VarTable::~VarTable() {
        for (std::map<std::string, ObjectType *>::iterator it = varTypes.begin(); it != varTypes.end(); it++) {
            delete it->second;
        }
    }
} // karl