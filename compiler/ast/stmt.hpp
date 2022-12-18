#ifndef KARL_STMT_HPP
#define KARL_STMT_HPP

namespace karl {

    enum class StmtType {
        _,
        Expr,
        FuncDef,
        VarDef,
        If,
        While,
        Break,
        Continue,
        Return
    };

    struct Stmt {
        int line;
        int column;

        virtual StmtType stmtType() = 0;
    };

} // karl

#endif //KARL_STMT_HPP
