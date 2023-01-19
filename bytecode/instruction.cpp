#include "instruction.hpp"

namespace karl {
    namespace bytecode {
        Instruction1Number::Instruction1Number(OpCode opCode, int num) {
            this->opCode = opCode;
            this->num = num;
        }

        InstructionType Instruction1Number::introductionType() {
            return InstructionType::With1Number;
        }

        Instruction0Number::Instruction0Number(OpCode opCode) {
            this->opCode = opCode;
        }

        InstructionType Instruction0Number::introductionType() {
            return InstructionType::With0Number;
        }

        Instruction2Number::Instruction2Number(OpCode opCode, int numA, int numB) {
            this->opCode = opCode;
            this->numA = numA;
            this->numB = numB;
        }

        InstructionType Instruction2Number::introductionType() {
            return InstructionType::With2Number;
        }
    }
}