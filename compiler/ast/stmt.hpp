#ifndef KARL_STMT_HPP
#define KARL_STMT_HPP

#include "expr.hpp"
#include "var_table.hpp"

namespace karl {

    enum class StmtType {
        _,
        Block,
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
        virtual ~Stmt();
    };

    struct Block : public Stmt {
        std::vector<Stmt *> stmts;
        bool isLoopBlock;
        VarTable *varTable;

        Block(bool isLoopBlock, int line, int column);
        StmtType stmtType() override;
        ~Block() override;
    };

    struct ExprStmt : public Stmt {
        Expr *expr;

        ExprStmt(Expr *expr, int line, int column);
        StmtType stmtType() override;
        ~ExprStmt() override;
    };

    struct FuncDefStmt : public Stmt {
        Expr *name;
        std::vector<Expr *> parameters;
        std::vector<ObjectType *> parameterTypes;
        Block *block;

        ObjectType *objectType;

        FuncDefStmt(Expr *name, Block *block, int line, int column);
        StmtType stmtType() override;
        ~FuncDefStmt() override;
    };

    struct VarDefStmt : public Stmt {
        std::vector<Expr *> vars;
        std::vector<ObjectType *> types;
        std::vector<Expr *> initValues;

        VarDefStmt(int line, int column);
        StmtType stmtType() override;
        ~VarDefStmt() override;
    };

    struct IfStmt : public Stmt {
        std::vector<Expr *> conditions;
        std::vector<Block *> blocks;

        IfStmt(int line, int column);
        StmtType stmtType() override;
        ~IfStmt() override;
    };

    struct WhileStmt : public Stmt {
        Expr *condition;
        Block *block;

        WhileStmt(Expr *condition, Block *block, int line, int column);
        StmtType stmtType() override;
        ~WhileStmt() override;
    };

    struct BreakStmt : public Stmt {

        BreakStmt(int line, int column);
        StmtType stmtType() override;
        ~BreakStmt() override;
    };

    struct ContinueStmt : public Stmt {
        ContinueStmt(int line, int column);
        StmtType stmtType() override;
        ~ContinueStmt() override;
    };

    struct ReturnStmt : public Stmt {
        Expr *expr;

        ReturnStmt(Expr *expr, int line, int column);
        StmtType stmtType() override;
        ~ReturnStmt() override;
    };

} // karl

#endif //KARL_STMT_HPP
