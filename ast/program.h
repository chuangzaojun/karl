#ifndef KARL_PROGRAM_H
#define KARL_PROGRAM_H

#include "stmt.h"

struct Program {
    std::vector<Stmt *> stmts;
};

#endif // KARL_PROGRAM_H
