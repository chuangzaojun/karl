#ifndef KARL_VM_HPP
#define KARL_VM_HPP

#include "frame.hpp"
#include "heap.hpp"
#include "../bytecode/bytecode.hpp"
#include <list>

namespace karl {
    namespace vm {
        class VM {
        private:
            bytecode::Bytecode *bytecode;
            std::list<Frame *> stack;
            Frame *curFrame;

            std::vector<Object *> globalVars;

            Heap *heap;

            void pushFrame(int funcIndex);
            void popFrame();

            void runFuncCall(int argumentNum, int funcIndex);
            void runNativeFuncCall(int argumentNum, int funcIndex);
            void runPushIntConst(int index);
            void runPushCharConst(int index);
            void runPushStringConst(int index);
            void runPushGlobalVar(int index);
            void runPushLocalVar(int index);
            void runSetGlobalVar(int index);
            void runSetLocalVar(int index);
            void runGotoIfTrue(int newPc);
            void runGotoIfFalse(int newPc);
            void runGoto(int newPc);
            void runMakeArray(int size);

            void runReturn();
            void runReturnNull();
            void runPushTrue();
            void runPushFalse();
            void runPop();
            void runSetArrayIndex();
            void runGetArrayIndex();
            void runMinus();
            void runAdd();
            void runMul();
            void runDiv();
            void runMod();
            void runLessThan();
            void runLessEqual();
            void runGreaterThan();
            void runGreaterEqual();
            void runEqual();
            void runNotEqual();
            void runAnd();
            void runOr();
            void runBAnd();
            void runBOr();
            void runBXor();
            void runLMove();
            void runRMove();
            void runPreMinus();
            void runNot();
            void runBNot();
            void runTypeToInt();
            void runTypeToString();
            void runTypeToChar();
            void runTypeToBool();

        public:
            VM(bytecode::Bytecode *bytecode, Heap *heap);
            void run();
        };
    }

}

#endif //KARL_VM_HPP
