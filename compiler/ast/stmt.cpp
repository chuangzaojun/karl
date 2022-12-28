#include "stmt.hpp"

namespace karl {
    Block::Block(bool isLoopBlock, int line, int column) {
        this->isLoopBlock = isLoopBlock;
        this->line = line;
        this->column = column;
    }

    StmtType Block::stmtType() {
        return StmtType::Block;
    }

    Block::~Block() {
        for (Stmt *i: stmts) {
            delete i;
        }
        delete varTable;
    }

    ExprStmt::ExprStmt(Expr *expr, int line, int column) {
        this->expr = expr;
        this->line = line;
        this->column = column;
    }

    StmtType ExprStmt::stmtType() {
        return StmtType::Expr;
    }

    ExprStmt::~ExprStmt() {
        delete expr;
    }

    FuncDefStmt::FuncDefStmt(Expr *name, Block *block, int line, int column) {
        this->name = name;
        this->block = block;
        this->line = line;
        this->column = column;
    }

    StmtType FuncDefStmt::stmtType() {
        return StmtType::FuncDef;
    }

    FuncDefStmt::~FuncDefStmt() {
        delete name;
        for (Expr *i: parameters) {
            delete i;
        }
        delete block;
    }

    VarDefStmt::VarDefStmt(int line, int column) {
        this->line = line;
        this->column = column;
    }

    StmtType VarDefStmt::stmtType() {
        return StmtType::VarDef;
    }

    VarDefStmt::~VarDefStmt() {
        for (Expr *i: vars) {
            delete i;
        }
        for (ObjectType *i: types) {
            delete i;
        }
        for (Expr *i: initValues) {
            delete i;
        }
    }

    IfStmt::IfStmt(int line, int column) {
        this->line = line;
        this->column = column;
    }

    StmtType IfStmt::stmtType() {
        return StmtType::If;
    }

    IfStmt::~IfStmt() {
        for (Expr *i: conditions) {
            delete i;
        }
        for (Block *i: blocks) {
            delete i;
        }
    }

    WhileStmt::WhileStmt(Expr *condition, Block *block, int line, int column) {
        this->condition = condition;
        this->block = block;
        this->line = line;
        this->column = column;
    }

    StmtType WhileStmt::stmtType() {
        return StmtType::While;
    }

    WhileStmt::~WhileStmt() {
        delete condition;
        delete block;
    }

    BreakStmt::BreakStmt(int line, int column) {
        this->line = line;
        this->column = column;
    }

    StmtType BreakStmt::stmtType() {
        return StmtType::Break;
    }

    BreakStmt::~BreakStmt() {}

    ContinueStmt::ContinueStmt(int line, int column) {
        this->line = line;
        this->column = column;
    }

    StmtType ContinueStmt::stmtType() {
        return StmtType::Continue;
    }

    ContinueStmt::~ContinueStmt() {}

    ReturnStmt::ReturnStmt(Expr *expr, int line, int column) {
        this->expr = expr;
        this->line = line;
        this->column = column;
    }

    StmtType ReturnStmt::stmtType() {
        return StmtType::Return;
    }

    ReturnStmt::~ReturnStmt() {
        delete expr;
    }

    Stmt::~Stmt() {}
} // karl