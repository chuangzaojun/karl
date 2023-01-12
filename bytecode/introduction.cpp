#include "introduction.hpp"

namespace karl {
    namespace bytecode {
        Introduction1Number::Introduction1Number(OpCode opCode, int num) {
            this->opCode = opCode;
            this->num = num;
        }

        IntroductionType Introduction1Number::introductionType() {
            return IntroductionType::With1Number;
        }

        Introduction0Number::Introduction0Number(OpCode opCode) {
            this->opCode = opCode;
        }

        IntroductionType Introduction0Number::introductionType() {
            return IntroductionType::With0Number;
        }
    }
}