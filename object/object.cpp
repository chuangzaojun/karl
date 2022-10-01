#include "object.h"

ObjectType IntObject::type() {
    return OBJECT_INT;
}

ObjectType BoolObject::type() {
    return OBJECT_BOOL;
}

bool getBoolValue(Object *object) {
    if (object->type() == OBJECT_BOOL) {
        return ((BoolObject *) object)->value;
    }
    return ((IntObject *) object)->value != 0;
}

int getIntValue(Object *object) {
    if (object->type() == OBJECT_BOOL) {
        if (((BoolObject *) object)->value == true) {
            return 1;
        }
        return 0;
    }
    return ((IntObject *) object)->value;
}

Object *add(Object *left, Object *right) {
    IntObject *object = new IntObject{};
    object->value = getIntValue(left) + getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *minus(Object *left, Object *right) {
    IntObject *object = new IntObject{};
    object->value = getIntValue(left) - getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *mul(Object *left, Object *right) {
    IntObject *object = new IntObject{};
    object->value = getIntValue(left) * getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *div(Object *left, Object *right) {
    IntObject *object = new IntObject{};
    object->value = getIntValue(left) / getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *mod(Object *left, Object *right) {
    IntObject *object = new IntObject{};
    object->value = getIntValue(left) % getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *eq(Object *left, Object *right) {
    BoolObject *object = new BoolObject{};
    object->value = getIntValue(left) == getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *ne(Object *left, Object *right) {
    BoolObject *object = new BoolObject{};
    object->value = getIntValue(left) != getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *gt(Object *left, Object *right) {
    BoolObject *object = new BoolObject{};
    object->value = getIntValue(left) > getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *ge(Object *left, Object *right) {
    BoolObject *object = new BoolObject{};
    object->value = getIntValue(left) >= getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *lt(Object *left, Object *right) {
    BoolObject *object = new BoolObject{};
    object->value = getIntValue(left) < getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *le(Object *left, Object *right) {
    BoolObject *object = new BoolObject{};
    object->value = getIntValue(left) <= getIntValue(right);
    delete left;
    delete right;
    return object;
}

Object *no(Object *right) {
    BoolObject *object = new BoolObject{};
    object->value = !getBoolValue(right);
    delete right;
    return object;
}

Object *minus(Object *right) {
    IntObject *object = new IntObject{};
    object->value = -getIntValue(right);
    delete right;
    return object;
}

Object *copy(Object *object) {
    if (object->type() == OBJECT_INT) {
        IntObject *n_object = new IntObject{};
        n_object->value = getIntValue(object);
        return n_object;
    }
    BoolObject *n_object = new BoolObject{};
    n_object->value = getBoolValue(object);
    return n_object;
}

ObjectType Object::type() {
    return OBJECT;
}
