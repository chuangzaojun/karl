#include "object.hpp"

namespace karl {
    namespace vm {

        IntObject::IntObject(int value) {
            this->value = value;
        }

        SingleObjectType IntObject::type() {
            return SingleObjectType::Int;
        }


        BoolObject::BoolObject(bool value) {
            this->value = value;
        }

        SingleObjectType BoolObject::type() {
            return SingleObjectType::Bool;
        }

        StringObject::StringObject(std::string value) {
            this->value = value;
        }

        SingleObjectType StringObject::type() {
            return SingleObjectType::String;
        }

        CharObject::CharObject(char value) {
            this->value = value;
        }

        SingleObjectType CharObject::type() {
            return SingleObjectType::Char;
        }

        ArrayObject::ArrayObject(int size) {
            value.resize(size);
        }

        SingleObjectType ArrayObject::type() {
            return SingleObjectType::Array;
        }
    }
}