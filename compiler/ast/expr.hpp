#ifndef KARL_EXPR_HPP
#define KARL_EXPR_HPP

#include <string>
#include <vector>

namespace karl {

    enum class ExprType {
        _,
        Identifier, // done
        Int, // done
        Char, // done
        True, // done
        False, // done
        String, // done
        Binary,  // done
        Prefix, // done
        FuncCall, // done
        Assign, // done
        ArrayIndex, // done
        ArrayLiteral // done
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

        BinaryExpr(Expr *_left, OpType _op, Expr *_right, int _line, int _column);
        ExprType type() override;
        ~BinaryExpr() override;
    };

    struct PrefixExpr : public Expr {
        OpType op;
        Expr *right;

        PrefixExpr(OpType _op, Expr *_right, int _line, int _column);
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
        FalseExpr(int _line, int _column);
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
        std::vector<Expr *> arguments;

        FuncCallExpr(Expr *_id, int _line, int _column);
        ExprType type() override;
        ~FuncCallExpr() override;
    };

    struct AssignExpr : public Expr {
        Expr *left;
        Expr *right;

        AssignExpr(Expr *_left, Expr *_right, int _line, int _column);
        ExprType type() override;
        ~AssignExpr();
    };

    struct ArrayIndexExpr : public Expr {
        Expr *array;
        Expr *index;

        AssignExpr(Expr *_array, Expr *_index, int _line, int _column);
        ExprType type() override;
        ~ArrayIndexExpr();
    };

    struct ArrayLiteralExpr : public Expr {
        std::vector<Expr *> exprs;

        ArrayLiteralExpr(int _line, int _column);
        ExprType type() override;
        ~ArrayLiteralExpr() override;
    };
} // karl

#endif //KARL_EXPR_HPP
