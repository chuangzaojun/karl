#ifndef KARL_OBJECT_HPP
#define KARL_OBJECT_HPP

#include <string>
#include <vector>

namespace karl {
    namespace vm {
        enum class SingleObjectType {
            _,
            Int,
            Bool,
            String,
            Char,
            Void,
            Array
        };

        struct Object {
            virtual int getIntValue() = 0;
            virtual char getCharValue() = 0;
            virtual bool getBoolValue() = 0;
            virtual std::string getStringValue() = 0;
            virtual SingleObjectType type() = 0;
        };

        struct IntObject : public Object {
            int value;

            IntObject(int value);
            int getIntValue() override;
            char getCharValue() override;
            bool getBoolValue() override;
            std::string getStringValue() override;
            SingleObjectType type() override;
        };

        struct BoolObject : public Object {
            bool value;

            BoolObject(bool value);
            int getIntValue() override;
            char getCharValue() override;
            bool getBoolValue() override;
            std::string getStringValue() override;
            SingleObjectType type() override;
        };

        struct CharObject : public Object {
            char value;

            CharObject(char value);
            int getIntValue() override;
            char getCharValue() override;
            bool getBoolValue() override;
            std::string getStringValue() override;
            SingleObjectType type() override;
        };

        struct StringObject : public Object {
            std::string value;

            StringObject(std::string value);
            int getIntValue() override;
            char getCharValue() override;
            bool getBoolValue() override;
            std::string getStringValue() override;
            SingleObjectType type() override;
        };

        struct ArrayObject : public Object {
            std::vector<Object *> value;

            ArrayObject(int size);
            int getIntValue() override;
            char getCharValue() override;
            bool getBoolValue() override;
            std::string getStringValue() override;
            SingleObjectType type() override;
        };
    }
}

#endif //KARL_OBJECT_HPP
