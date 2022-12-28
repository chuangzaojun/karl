#ifndef KARL_VAR_TABLE_HPP
#define KARL_VAR_TABLE_HPP

#include "object_type.hpp"
#include <map>
#include <string>

namespace karl {

    class VarTable {
    private:
        std::map<std::string, ObjectType *> varTypes;
        VarTable *outer;

    public:
        VarTable(VarTable *outer);
        void set(std::string var, ObjectType *type, int line, int column);
        ObjectType *get(std::string var, int line, int column);
        ~VarTable();
    };

} // karl

#endif //KARL_VAR_TABLE_HPP
