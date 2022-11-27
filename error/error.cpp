
#include "error.hpp"
#include <iostream>

namespace karl {
    void error(ErrorType type, int line, int column) {
        switch (type) {
            case ErrorType::LexError:
                printf("Unknown token at line %d, column %d.\n", line, column);
        }
        exit(0);
    }
} // karl