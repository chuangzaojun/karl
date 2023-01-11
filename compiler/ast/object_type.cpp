#include "object_type.hpp"

namespace karl {
    namespace compiler {
        SingleObjectType IntObject::singleObjectType() {
            return SingleObjectType::Int;
        }

        ObjectType *IntObject::copy() {
            return new IntObject();
        }

        IntObject::~IntObject() {}

        bool IntObject::isEqual(ObjectType *type) {
            return type->singleObjectType() == SingleObjectType::Int;
        }

        std::string IntObject::toString() {
            return "int";
        }

        SingleObjectType BoolObject::singleObjectType() {
            return SingleObjectType::Bool;
        }

        ObjectType *BoolObject::copy() {
            return new BoolObject();
        }

        BoolObject::~BoolObject() {}

        bool BoolObject::isEqual(ObjectType *type) {
            return type->singleObjectType() == SingleObjectType::Bool;
        }

        std::string BoolObject::toString() {
            return "bool";
        }

        SingleObjectType StringObject::singleObjectType() {
            return SingleObjectType::String;
        }

        ObjectType *StringObject::copy() {
            return new StringObject();
        }

        StringObject::~StringObject() {}

        bool StringObject::isEqual(ObjectType *type) {
            return type->singleObjectType() == SingleObjectType::String;
        }

        std::string StringObject::toString() {
            return "string";
        }

        SingleObjectType CharObject::singleObjectType() {
            return SingleObjectType::Char;
        }

        ObjectType *CharObject::copy() {
            return new CharObject;
        }

        CharObject::~CharObject() {}

        bool CharObject::isEqual(ObjectType *type) {
            return type->singleObjectType() == SingleObjectType::Char;
        }

        std::string CharObject::toString() {
            return "char";
        }

        SingleObjectType VoidObject::singleObjectType() {
            return SingleObjectType::Void;
        }

        ObjectType *VoidObject::copy() {
            return new VoidObject;
        }

        VoidObject::~VoidObject() {}

        bool VoidObject::isEqual(ObjectType *type) {
            return type->singleObjectType() == SingleObjectType::Void;
        }

        std::string VoidObject::toString() {
            return "void";
        }

        ArrayObject::ArrayObject(ObjectType *memberType, int memberNum) {
            this->memberType = memberType;
            this->memberNum = memberNum;
        }

        SingleObjectType ArrayObject::singleObjectType() {
            return SingleObjectType::Array;
        }

        ObjectType *ArrayObject::copy() {
            return new ArrayObject(memberType->copy(), memberNum);
        }

        ArrayObject::~ArrayObject() {
            delete memberType;
        }

        bool ArrayObject::isEqual(ObjectType *type) {
            if (type->singleObjectType() == SingleObjectType::Array) {
                if (((ArrayObject *) type)->memberNum == memberNum) {
                    return memberType->isEqual(((ArrayObject *) type)->memberType);
                }
                return false;
            }
            return false;
        }

        std::string ArrayObject::toString() {
            return memberType->toString() + "[" + std::to_string(memberNum) + "]";
        }

        ObjectType::~ObjectType() {}
    }
}