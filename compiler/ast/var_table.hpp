#ifndef KARL_VAR_TABLE_HPP
#define KARL_VAR_TABLE_HPP

#include "object_type.hpp"
#include <map>
#include <string>

namespace karl {
    namespace compiler {
        class VarTable {
        private:
            std::map<std::string, ObjectType *> varTypes;
            std::map<std::string, int> varIndexes;
            VarTable *outer;

        public:
            VarTable(VarTable *outer);
            void set(std::string var, ObjectType *type, int line, int column);
            bool isLocalVar(std::string var);
            int localVarNum();
            int globalVarNum();
            ObjectType *getType(std::string var, int line, int column);
            int getIndex(std::string var);
        };
    }

}

#endif //KARL_VAR_TABLE_HPP
