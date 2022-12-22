#include "expr.hpp"

namespace karl {


    BinaryExpr::BinaryExpr(Expr *left, OpType op, Expr *right, int line, int column) {
        this->left = left;
        this->op = op;
        this->right = right;
        this->line = line;
        this->column = column;
    }

    ExprType BinaryExpr::exprType() {
        return ExprType::Binary;
    }

    BinaryExpr::~BinaryExpr() {
        delete left;
        delete right;
    }


    PrefixExpr::PrefixExpr(OpType op, Expr *right, int line, int column) {
        this->op = op;
        this->right = right;
        this->line = line;
        this->column = column;
    }

    ExprType PrefixExpr::exprType() {
        return ExprType::Prefix;
    }

    PrefixExpr::~PrefixExpr() {
        delete right;
    }

    AssignExpr::AssignExpr(Expr *left, Expr *right, int line, int column) {
        this->left = left;
        this->right = right;
        this->line = line;
        this->column = column;
    }

    ExprType AssignExpr::exprType() {
        return ExprType::Assign;
    }

    AssignExpr::~AssignExpr() {
        delete left;
        delete right;
    }

    IdentifierExpr::IdentifierExpr(std::string identifier, int line, int column) {
        this->line = line;
        this->column = column;
    }

    ExprType IdentifierExpr::exprType() {
        return ExprType::Identifier;
    }

    IdentifierExpr::~IdentifierExpr() {}

    FuncCallExpr::FuncCallExpr(Expr *name, int line, int column) {
        this->name = name;
        this->line = line;
        this->column = column;
    }

    ExprType FuncCallExpr::exprType() {
        return ExprType::FuncCall;
    }

    FuncCallExpr::~FuncCallExpr() {
        delete name;
        for (Expr *i: parameters) {
            delete i;
        }
    }

    ArrayIndexExpr::ArrayIndexExpr(Expr *array, Expr *index, int line, int column) {
        this->array = array;
        this->index = index;
        this->line = line;
        this->column = column;
    }

    ExprType ArrayIndexExpr::exprType() {
        return ExprType::ArrayIndex;
    }

    ArrayIndexExpr::~ArrayIndexExpr() {
        delete array
        delete index;
    }

    ArrayLiteralExpr::ArrayLiteralExpr(int line, int column) {
        this->line = line;
        this->column = column;
    }

    ExprType ArrayLiteralExpr::exprType() {
        return ExprType::ArrayLiteral;
    }

    ArrayLiteralExpr::~ArrayLiteralExpr() {
        for (Expr *i: exprs) {
            delete i;
        }
    }

    Expr::~Expr() {
        delete objectType;
    }

    IntExpr::IntExpr(int value, int line, int column) {
        this->value = value;
        this->line = line;
        this->column = column;
    }

    ExprType IntExpr::exprType() {
        return ExprType::Int;
    }

    IntExpr::~IntExpr() {}

    CharExpr::CharExpr(char value, int line, int column) {
        this->value = value;
        this->line = line;
        this->column = column;
    }

    ExprType CharExpr::exprType() {
        return ExprType::Char;
    }

    CharExpr::~CharExpr() {}

    StringExpr::StringExpr(std::string value, int line, int column) {
        this->value = value;
        this->line = line;
        this->column = column;
    }

    ExprType StringExpr::exprType() {
        return ExprType::String;
    }

    StringExpr::~StringExpr() {}

    BoolExpr::BoolExpr(bool value, int line, int column) {
        this->value = value;
        this->line = line;
        this->column = column;
    }

    ExprType BoolExpr::exprType() {
        return ExprType::Bool;
    }

    BoolExpr::~BoolExpr() {}
} // karl