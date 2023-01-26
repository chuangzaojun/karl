#include "instruction.hpp"
#include <map>

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

        std::map<OpCode, std::string> opCodeToString = {
                {OpCode::FuncCall, "FuncCall"},
                {OpCode::NativeFuncCall, "NativeFuncCall"},
                {OpCode::PushIntConst, "PushIntConst"},
                {OpCode::PushCharConst, "PushCharConst"},
                {OpCode::PushStringConst, "PushStringConst"},
                {OpCode::PushGlobalVar, "PushGlobalVar"},
                {OpCode::PushLocalVar, "PushLocalVar"},
                {OpCode::SetGlobalVar, "SetGlobalVar"},
                {OpCode::SetLocalVar, "SetLocalVar"},
                {OpCode::GotoIfFalse, "GotoIfFalse"},
                {OpCode::GotoIfTrue, "GotoIfTrue"},
                {OpCode::Goto, "Goto"},
                {OpCode::MakeArray, "MakeArray"},
                {OpCode::Return, "Return"},
                {OpCode::ReturnNull, "ReturnNull"},
                {OpCode::PushTrue, "PushTrue"},
                {OpCode::PushFalse, "PushFalse"},
                {OpCode::Pop, "Pop"},
                {OpCode::SetArrayIndex, "SetArrayIndex"},
                {OpCode::GetArrayIndex, "GetArrayIndex"},
                {OpCode::Minus, "Minus"},
                {OpCode::Add, "Add"},
                {OpCode::Mul, "Mul"},
                {OpCode::Div, "Div"},
                {OpCode::Mod, "Mod"},
                {OpCode::LessThan, "LessThan"},
                {OpCode::LessEqual, "LessEqual"},
                {OpCode::GreaterThan, "GreaterThan"},
                {OpCode::GreaterEqual, "GreaterEqual"},
                {OpCode::Equal, "Equal"},
                {OpCode::NotEqual, "NotEqual"},
                {OpCode::And, "And"},
                {OpCode::Or, "Or"},
                {OpCode::BAnd, "BAnd"},
                {OpCode::BOr, "BOr"},
                {OpCode::BXor, "BXor"},
                {OpCode::LMove, "LMove"},
                {OpCode::RMove, "RMove"},
                {OpCode::PreMinus, "PreMinus"},
                {OpCode::Not, "Not"},
                {OpCode::BNot, "BNot"},
                {OpCode::TypeToInt, "TypeToInt"},
                {OpCode::TypeToString, "TypeToString"},
                {OpCode::TypeToChar, "TypeToChar"},
                {OpCode::TypeToBool, "TypeToBool"}
        };

        std::string Instruction2Number::toString() {
            return opCodeToString[opCode] + " " + std::to_string(numA) + " " + std::to_string(numB);
        }

        std::string Instruction1Number::toString() {
            return opCodeToString[opCode] + " " + std::to_string(num);
        }

        std::string Instruction0Number::toString() {
            return opCodeToString[opCode];
        }
    }
}