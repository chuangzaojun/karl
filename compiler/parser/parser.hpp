#ifndef KARL_PARSER_HPP
#define KARL_PARSER_HPP

#include "../lexer/lexer.hpp"
#include "../ast/program.hpp"

namespace karl {

    class Parser {
    private:
        Lexer *lexer;

        Stmt *parseStmt();


    public:
        Parser(Lexer *lexer);
        Program *parseProgram();
    };

} // karl

#endif //KARL_PARSER_HPP
