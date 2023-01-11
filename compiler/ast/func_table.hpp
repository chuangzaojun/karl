#ifndef KARL_FUNC_TABLE_HPP
#define KARL_FUNC_TABLE_HPP

#include "object_type.hpp"
#include "stmt.hpp"
#include <map>
#include <string>

namespace karl {

    namespace compiler {

        class FuncTable {
        private:
            std::map<std::string, FuncDefStmt *> funcStmts;
            std::map<std::string, int> funcIndexes;

        public:
            FuncTable();
            void set(std::string func, FuncDefStmt *stmt, int line, int column);
            int getIndex(std::string func);
            int funcNum();
            FuncDefStmt *getStmt(std::string func, int line, int column);
        };
    }

}

#endif //KARL_FUNC_TABLE_HPP
