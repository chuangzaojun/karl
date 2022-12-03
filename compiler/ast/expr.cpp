#include "expr.hpp"

namespace karl {
    BinaryExpr::BinaryExpr(Expr *_left, OpType _op, Expr *_right, int _line, int _column) {
        left = _left;
        op = _op;
        right = _right;
        line = _line;
        column = _column;
    }

    ExprType BinaryExpr::type() {
        return ExprType::Binary;
    }

    BinaryExpr::~BinaryExpr() {
        delete left;
        delete right;
    }


    PrefixExpr::PrefixExpr(OpType _op, Expr *_right, int _line, int _column) {
        op = _op;
        right = _right;
        line = _line;
        column = _column;
    }

    ExprType PrefixExpr::type() {
        return ExprType::Prefix;
    }

    PrefixExpr::~PrefixExpr() {
        delete right;
    }

    IdentifierExpr::IdentifierExpr(std::string _identifier, int _line, int _column) {
        identifier = identifier;
        line = _line;
        column = _column;
    }

    ExprType IdentifierExpr::type() {
        return ExprType::Identifier;
    }

    IdentifierExpr::~IdentifierExpr() {
        ;
    }

    IntExpr::IntExpr(int _value, int _line, int _column) {
        value = _value;
        line = _line;
        column = _column;
    }

    ExprType IntExpr::type() {
        return ExprType::Int;
    }

    IntExpr::~IntExpr() {
        ;
    }

    CharExpr::CharExpr(char _value, int _line, int _column) {
        value = _value;
        line = _line;
        column = _column;
    }

    ExprType CharExpr::type() {
        return ExprType::Char;
    }

    CharExpr::~CharExpr() {
        ;
    }

    TrueExpr::TrueExpr(int _line, int _column) {

    }

    ExprType TrueExpr::type() {
        return ExprType::ArrayLiteral;
    }

    TrueExpr::~TrueExpr() {

    }

    FalseExpr::FalseExpr(int _line, int _column) {

    }

    ExprType FalseExpr::type() {
        return ExprType::ArrayLiteral;
    }

    FalseExpr::~FalseExpr() {

    }

    StringExpr::StringExpr(std::string _value, int _line, int _column) {

    }

    ExprType StringExpr::type() {
        return ExprType::ArrayLiteral;
    }

    StringExpr::~StringExpr() {

    }

    FuncCallExpr::FuncCallExpr(Expr *_id, int _line, int _column) {

    }

    ExprType FuncCallExpr::type() {
        return ExprType::ArrayLiteral;
    }

    FuncCallExpr::~FuncCallExpr() {

    }
} // karl