#ifndef KARL_INTRODUCTION_HPP
#define KARL_INTRODUCTION_HPP

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

        enum class IntroductionType {
            _,
            With2Number,
            With1Number,
            With0Number
        };

        struct Introduction {
            OpCode opCode;

            virtual IntroductionType introductionType() = 0;
        };

        struct Introduction2Number : public Introduction {
            int numA;
            int numB;

            Introduction2Number(OpCode opCode, int numA, int numB);
            IntroductionType introductionType() override;
        };

        struct Introduction1Number : public Introduction {
            int num;

            Introduction1Number(OpCode opCode, int num);
            IntroductionType introductionType() override;
        };

        struct Introduction0Number : public Introduction {
            Introduction0Number(OpCode opCode);
            IntroductionType introductionType() override;
        };
    }
}

#endif //KARL_INTRODUCTION_HPP
