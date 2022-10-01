#ifndef KARL_OBJECT_H
#define KARL_OBJECT_H

enum ObjectType {
    OBJECT,
    OBJECT_INT,
    OBJECT_BOOL
};

struct Object {
    virtual ObjectType type();
};

struct IntObject : public Object {
    ObjectType type() override;

    int value{};
};

struct BoolObject : public Object {
    ObjectType type() override;

    bool value{};
};

bool getBoolValue(Object *object);

int getIntValue(Object *object);

Object *add(Object *left, Object *right); // +
Object *minus(Object *left, Object *right); // -
Object *mul(Object *left, Object *right); // *
Object *div(Object *left, Object *right); // /
Object *mod(Object *left, Object *right); // %
Object *eq(Object *left, Object *right); // ==
Object *ne(Object *left, Object *right); // !=
Object *gt(Object *left, Object *right); // >
Object *ge(Object *left, Object *right); // >=
Object *lt(Object *left, Object *right); // <
Object *le(Object *left, Object *right); // <=
Object *no(Object *right);  // !
Object *minus(Object *right); // -
Object *copy(Object *object);

#endif // KARL_OBJECT_H
