#ifndef KARL_TYPE_CHECKER_HPP
#define KARL_TYPE_CHECKER_HPP

#include "../ast/program.hpp"

namespace karl {

    class TypeChecker {
    private:
        Program *program;
        Block *curBlock;
        Block *curLoopBlock;

    public:
        TypeChecker(Program *program);
        void checkProgram();
    };

} // karl

#endif //KARL_TYPE_CHECKER_HPP
