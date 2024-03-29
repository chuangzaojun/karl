#include "object.hpp"

namespace karl {
    namespace vm {

        IntObject::IntObject(int value) {
            color = ObjectColor::White;
            this->value = value;
        }

        int IntObject::getIntValue() {
            return value;
        }

        char IntObject::getCharValue() {
            return (char) value;
        }

        bool IntObject::getBoolValue() {
            return (bool) value;
        }

        std::string IntObject::getStringValue() {
            return std::to_string(value);
        }

        SingleObjectType IntObject::type() {
            return SingleObjectType::Int;
        }

        void IntObject::mark() {
            color = ObjectColor::Black;
        }

        BoolObject::BoolObject(bool value) {
            color = ObjectColor::White;
            this->value = value;
        }

        int BoolObject::getIntValue() {
            return (int) value;
        }

        char BoolObject::getCharValue() {
            return (char) value;
        }

        bool BoolObject::getBoolValue() {
            return value;
        }

        std::string BoolObject::getStringValue() {
            if (value == true) {
                return "true";
            }
            return "false";
        }

        SingleObjectType BoolObject::type() {
            return SingleObjectType::Bool;
        }

        void BoolObject::mark() {
            color = ObjectColor::Black;
        }

        CharObject::CharObject(char value) {
            color = ObjectColor::White;
            this->value = value;
        }

        int CharObject::getIntValue() {
            return (int) value;
        }

        char CharObject::getCharValue() {
            return value;
        }

        bool CharObject::getBoolValue() {
            return (bool) value;
        }

        std::string CharObject::getStringValue() {
            std::string st;
            st += value;
            return st;
        }

        SingleObjectType CharObject::type() {
            return SingleObjectType::Char;
        }

        void CharObject::mark() {
            color = ObjectColor::Black;
        }

        StringObject::StringObject(std::string value) {
            color = ObjectColor::White;
            this->value = value;
        }

        int StringObject::getIntValue() {
            return std::stoi(value);
        }

        char StringObject::getCharValue() {
            return value[0];
        }

        bool StringObject::getBoolValue() {
            return value == "true";
        }

        std::string StringObject::getStringValue() {
            return value;
        }

        SingleObjectType StringObject::type() {
            return SingleObjectType::String;
        }

        void StringObject::mark() {
            color = ObjectColor::Black;
        }

        ArrayObject::ArrayObject(int size) {
            color = ObjectColor::White;
            value = std::vector<Object *>(size);
        }

        int ArrayObject::getIntValue() {
            return 0;
        }

        char ArrayObject::getCharValue() {
            return ' ';
        }

        bool ArrayObject::getBoolValue() {
            return false;
        }

        std::string ArrayObject::getStringValue() {
            return "";
        }

        SingleObjectType ArrayObject::type() {
            return SingleObjectType::Array;
        }

        void ArrayObject::mark() {
            color = ObjectColor::Black;
            for (Object *object: value) {
                object->color = ObjectColor::Grey;
            }
        }
    }
}
