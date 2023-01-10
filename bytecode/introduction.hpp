#ifndef KARL_INTRODUCTION_HPP
#define KARL_INTRODUCTION_HPP

namespace karl::bytecode {

    enum class OpCode {
        _,

        // 1 number
        PushIntConst,
        PushCharConst,
        PushStringConst,
        PushGlobalVar,
        PushLocalVar,
        SetGlobalVar,
        SetLocalVar,

        IfTrueGoto,
        IfFalseGoto,
        Goto,
        FuncCall,

        // 0 number
        Return,

        PushTrue,
        PushFalse,

        Pop,

        SetArrayIndex,
        GetArrayIndex,

        Assign, // =
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
        Not, // !

        BAnd, // &
        BOr, // |
        BNot, // ~
        BXor, // ^
        LMove, // <<
        RMove, // >>
    };

    enum class IntroductionType {
        _,
        With1Number,
        With0Number
    };

    struct Introduction {
        OpCode opCode;

        virtual IntroductionType introductionType() = 0;
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

} // karl

#endif //KARL_INTRODUCTION_HPP
