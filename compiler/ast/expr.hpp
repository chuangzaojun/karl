#ifndef KARL_EXPR_HPP
#define KARL_EXPR_HPP

#include <string>
#include <vector>

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
        Assign,
        ArrayIndex,
        ArrayLiteral
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
        std::string identifier;

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

    struct TrueExpr : public Expr {
        TrueExpr(int _line, int _column);
        ExprType type() override;
        ~TrueExpr() override;
    };


    struct FalseExpr : public Expr {
        FalseeExpr(int _line, int _column);
        ExprType type() override;
        ~FalseExpr() override;
    };

    struct StringExpr : public Expr {
        std::string value;

        StringExpr(std::string _value, int _line, int _column);
        ExprType type() override;
        ~StringExpr() override;
    };

    struct FuncCallExpr : public Expr {
        Expr *id;
        std::vector<Expr *> args;

        FuncCallExpr()
    };
} // karl

#endif //KARL_EXPR_HPP
