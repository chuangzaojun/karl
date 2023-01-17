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
            Array
        };

        struct Object {
            virtual SingleObjectType type() = 0;
        };

        struct IntObject : public Object {
            int value;

            IntObject(int value);
            SingleObjectType type() override;
        };

        struct BoolObject : public Object {
            bool value;

            BoolObject(bool value);
            SingleObjectType type() override;
        };

        struct StringObject : public Object {
            std::string value;

            StringObject(std::string value);
            SingleObjectType type() override;
        };

        struct CharObject : public Object {
            char value;

            CharObject(char value);
            SingleObjectType type() override;
        };

        struct ArrayObject : public Object {
            std::vector<Object *> value;

            ArrayObject(int size);
            SingleObjectType type() override;
        };
    }
}

#endif //KARL_OBJECT_HPP
