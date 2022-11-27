#ifndef KARL_EXPR_HPP
#define KARL_EXPR_HPP

namespace karl {

    enum class ExprType {
        _,
        IdentifierExpr,
        IntExpr,
        CharExpr,
        StringExpr,
        BinaryExpr,
        PrefixExpr,
        FuncCallExpr,
        AssignExpr
    };


    enum class ObjectType {
        _,
        IntObject,
        CharObject,
        StringObject,
        BoolObject
    };

    struct Expr {
        int line;
        ObjectType valueType;

        virtual ExprType type() = 0;
    };

} // karl

#endif //KARL_EXPR_HPP
