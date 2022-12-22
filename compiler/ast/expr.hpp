#ifndef KARL_EXPR_HPP
#define KARL_EXPR_HPP

#include "object_type.hpp"
#include <string>
#include <vector>

namespace karl {

    enum class ExprType {
        _,
        Binary,
        Prefix,
        Assign,
        Identifier,
        FuncCall,
        ArrayIndex,
        ArrayLiteral,
        Int,
        Char,
        String,
        Bool
    };

    enum class OpType {
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

    struct Expr {
        int line;
        int column;
        ObjectType *objectType;

        virtual ExprType exprType() = 0;
        virtual ~Expr();
    };

    struct BinaryExpr : public Expr {
        Expr *left;
        OpType op;
        Expr *right;

        BinaryExpr(Expr *left, OpType op, Expr *right, int line, int column);
        ExprType exprType() override;
        ~BinaryExpr() override;
    };

    struct PrefixExpr : public Expr {
        OpType op;
        Expr *right;

        PrefixExpr(OpType op, Expr *right, int line, int column);
        ExprType exprType() override;
        ~PrefixExpr() override;
    };

    struct AssignExpr : public Expr {
        Expr *left;
        Expr *right;

        AssignExpr(Expr *left, Expr *right, int line, int column);
        ExprType exprType() override;
        ~AssignExpr() override;
    };

    struct IdentifierExpr : public Expr {
        std::string identifier;

        IdentifierExpr(std::string identifier, int line, int column);
        ExprType exprType() override;
        ~IdentifierExpr() override;
    };

    struct FuncCallExpr : public Expr {
        Expr *name;
        std::vector<Expr *> argument;

        FuncCallExpr(Expr *name, int line, int column);
        ExprType exprType() override;
        ~FuncCallExpr() override;
    };

    struct ArrayIndexExpr : public Expr {
        Expr *array;
        Expr *index;

        ArrayIndexExpr(Expr *array, Expr *index, int line, int column);
        ExprType exprType() override;
        ~ArrayIndexExpr() override;
    };

    struct ArrayLiteralExpr : public Expr {
        std::vector<Expr *> exprs;

        ArrayLiteralExpr(int line, int column);
        ExprType exprType() override;
        ~ArrayLiteralExpr() override;
    };

    struct IntExpr : public Expr {
        int value;

        IntExpr(int value, int line, int column);
        ExprType exprType() override;
        ~IntExpr() override;
    };

    struct CharExpr : public Expr {
        char value;

        CharExpr(char value, int line, int column);
        ExprType exprType() override;
        ~CharExpr() override;
    };

    struct StringExpr : public Expr {
        std::string value;

        StringExpr(std::string value, int line, int column);
        ExprType exprType() override;
        ~StringExpr() override;
    };

    struct BoolExpr : public Expr {
        bool value;

        BoolExpr(bool value, int line, int column);
        ExprType exprType() override;
        ~BoolExpr() override;
    };

} // karl

#endif //KARL_EXPR_HPP
