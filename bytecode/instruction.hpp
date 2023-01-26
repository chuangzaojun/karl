#ifndef KARL_INSTRUCTION_HPP
#define KARL_INSTRUCTION_HPP

#include <string>

namespace karl {
    namespace bytecode {

        enum class OpCode {
            _,

            // 2 number

            FuncCall,
            NativeFuncCall,

            // 1 number
            PushIntConst,
            PushCharConst,
            PushStringConst,
            PushGlobalVar,
            PushLocalVar,
            SetGlobalVar,
            SetLocalVar,

            GotoIfTrue,
            GotoIfFalse,
            Goto,

            MakeArray,

            // 0 number
            Return,
            ReturnNull,

            PushTrue,
            PushFalse,

            Pop,

            SetArrayIndex,
            GetArrayIndex,

            // binary op
            Minus, // -
            Add, // +
            Mul, // *
            Div, // /
            Mod, // %
            LessThan, // <
            LessEqual, // <=
            GreaterThan, // >
            GreaterEqual, // >=
            Equal, // ==
            NotEqual, // !=

            And, // &&
            Or, // ||

            BAnd, // &
            BOr, // |
            BXor, // ^
            LMove, // <<
            RMove, // >>

            // prefix op
            PreMinus, // -
            Not, // !
            BNot, // ~

            TypeToInt,
            TypeToString,
            TypeToChar,
            TypeToBool
        };

        enum class InstructionType {
            _,
            With2Number,
            With1Number,
            With0Number
        };

        struct Instruction {
            OpCode opCode;

            virtual InstructionType introductionType() = 0;
            virtual std::string toString() = 0;
        };

        struct Instruction2Number : public Instruction {
            int numA;
            int numB;

            Instruction2Number(OpCode opCode, int numA, int numB);
            InstructionType introductionType() override;
            std::string toString() override;
        };

        struct Instruction1Number : public Instruction {
            int num;

            Instruction1Number(OpCode opCode, int num);
            InstructionType introductionType() override;
            std::string toString() override;
        };

        struct Instruction0Number : public Instruction {
            Instruction0Number(OpCode opCode);
            InstructionType introductionType() override;
            std::string toString() override;
        };
    }
}

#endif //KARL_INSTRUCTION_HPP
