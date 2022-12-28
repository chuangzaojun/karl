#ifndef KARL_FUNC_TABLE_HPP
#define KARL_FUNC_TABLE_HPP

#include "object_type.hpp"
#include "stmt.hpp"
#include <map>
#include <string>

namespace karl {

    class FuncTable {
    private:
        std::map<std::string, FuncDefStmt *> funcStmts;

    public:
        void set(std::string func, FuncDefStmt *stmt, int line, int column);
        FuncDefStmt *get(std::string func, int line, int column);
        ~FuncTable();
    };

} // karl

#endif //KARL_FUNC_TABLE_HPP
