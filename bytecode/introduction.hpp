#ifndef KARL_INTRODUCTION_HPP
#define KARL_INTRODUCTION_HPP

namespace karl::bytecode {

    enum class OpCode {
        PushIntConst,
        PushTrue,
        PushFalse,
        PushCharConst,
        PushStringConst,
        PushGlobalVar,
        PushLocalVar,

        Pop,

        AddInt,
        MinusInt,

    };

    struct Introduction {

    };

} // karl

#endif //KARL_INTRODUCTION_HPP
