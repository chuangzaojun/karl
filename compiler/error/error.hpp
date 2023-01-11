
#ifndef KARL_ERROR_HPP
#define KARL_ERROR_HPP

#include "../parser/lexer/token.hpp"
#include "../ast/expr.hpp"
#include "../ast/object_type.hpp"

namespace karl {

    namespace compiler {

        void lexError(int line, int column);

        void grammarError(TokenType expectType, Token *readToken);

        void grammarError(Token *readToken);

        class TypeError {
        public:
            static void varNotFoundError(std::string var, int line, int column);
            static void varHasDefError(std::string var, int line, int column);
            static void funcNotFoundError(std::string func, int line, int column);
            static void funcHasDefError(std::string func, int line, int column);
            static void invalidStmt(int line, int column);
            static void typeNotMatch(ObjectType *expectType, ObjectType *readType, int line, int column);
            static void typeNotAllowed(ObjectType *type, int line, int column);
            static void funcCallArgumentsNumNotMatch(int expectNum, int readNum, int line, int column);
            static void invalidOp(OpType op, int line, int column);
        };
    }
}

#endif //KARL_ERROR_HPP
