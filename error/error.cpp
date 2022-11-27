
#include "error.hpp"
#include <iostream>

namespace karl {
    void lexError(int line, int column) {
        printf("Unknown token at line %d, column %d.\n", line, column);
        exit(0);
    }
} // karl