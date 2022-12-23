#include "object_type.hpp"

namespace karl {
    SingleObjectType IntObject::singleObjectType() {
        return SingleObjectType::Int;
    }

    ObjectType *IntObject::copy() {
        return new IntObject();
    }

    IntObject::~IntObject() {}

    SingleObjectType BoolObject::singleObjectType() {
        return SingleObjectType::Bool;
    }

    ObjectType *BoolObject::copy() {
        return new BoolObject();
    }

    BoolObject::~BoolObject() {}

    SingleObjectType StringObject::singleObjectType() {
        return SingleObjectType::String;
    }

    ObjectType *StringObject::copy() {
        return new StringObject();
    }

    StringObject::~StringObject() {}

    SingleObjectType CharObject::singleObjectType() {
        return SingleObjectType::Char;
    }

    ObjectType *CharObject::copy() {
        return new CharObject;
    }

    CharObject::~CharObject() {}

    SingleObjectType VoidObject::singleObjectType() {
        return SingleObjectType::Void;
    }

    ObjectType *VoidObject::copy() {
        return new VoidObject;
    }

    VoidObject::~VoidObject() {}

    ArrayObject::ArrayObject(ObjectType *memberType) {
        this->memberType = memberType;
    }

    SingleObjectType ArrayObject::singleObjectType() {
        return SingleObjectType::Array;
    }

    ObjectType *ArrayObject::copy() {
        return new ArrayObject(memberType->copy());
    }

    ArrayObject::~ArrayObject() {
        delete memberType;
    }
} // karl