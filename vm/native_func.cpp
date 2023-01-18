#include "native_func.hpp"

namespace karl {
    namespace vm {
        void NativeFunc::print(std::vector<Object *> &arguments) {
            for (Object *object: arguments) {
                switch (object->type()) {
                    case SingleObjectType::Int:
                        printf("%d", ((IntObject *) object)->value);
                        break;
                    case SingleObjectType::Char:
                        printf("%c", ((CharObject *) object)->value);
                        break;
                    case SingleObjectType::String:
                        printf("%s", ((StringObject *) object)->value.data());
                        break;
                    case SingleObjectType::Bool:
                        if (((BoolObject *) object)->value == true) {
                            printf("true");
                        } else {
                            printf("false");
                        }
                        break;
                    case SingleObjectType::Array:
                        for (int i = 0; i < ((ArrayObject *) object)->value.size() - 1; i++) {
                            std::vector<Object *> temp;
                            temp.push_back(((ArrayObject *) object)->value[i]);
                            print(temp);
                            printf(" ");

                        }
                        std::vector<Object *> temp;
                        temp.push_back(((ArrayObject *) object)->value[((ArrayObject *) object)->value.size() - 1]);
                        print(temp);
                        break;
                }
            }
        }
    }
}