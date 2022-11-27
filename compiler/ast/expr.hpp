#ifndef KARL_EXPR_HPP
#define KARL_EXPR_HPP

#include <string>

namespace karl {

    enum class ExprType {
        _,
        Identifier,
        Int,
        Char,
        True,
        False,
        String,
        Binary,
        Prefix,
        FuncCall,
        Assign
    };


    enum class ObjectType {
        _,
        Int,
        Char,
        String,
        Bool
    };

    enum class OpType {
        _,
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
        ObjectType valueType;

        virtual ExprType type() = 0;
        virtual ~Expr() = 0;
    };

    struct BinaryExpr : public Expr {
        Expr *left;
        OpType op;
        Expr *right;

        BinaryExpr(Expr *_left, OpType _type, Expr *_right, int _line, int _column);
        ExprType type() override;
        ~BinaryExpr() override;
    };

    struct PrefixExpr : public Expr {
        OpType op;
        Expr *right;

        PrefixExpr(OpType _type, Expr *_right, int _line, int _column);
        ExprType type() override;
        ~PrefixExpr() override;
    };

    struct IdentifierExpr : public Expr {
        std::string identidier;

        IdentifierExpr(std::string _identifier, int _line, int _column);
        ExprType type() override;
        ~IdentifierExpr() override;
    };

    struct IntExpr : public Expr {
        int value;

        IntExpr(int _value, int _line, int _column);
        ExprType type() override;
        ~IntExpr() override;
    };

    struct CharExpr : public Expr {
        char value;

        CharExpr(char _value, int _line, int _column);
        ExprType type() override;
        ~CharExpr() override;
    };



} // karl

#endif //KARL_EXPR_HPP
