#ifndef KARL_OBJECT_TYPE_HPP
#define KARL_OBJECT_TYPE_HPP

#include <string>

namespace karl::compiler {

    enum class SingleObjectType {
        _,
        Int,
        Bool,
        String,
        Char,
        Void,
        Array
    };

    struct ObjectType {
        virtual SingleObjectType singleObjectType() = 0;
        virtual ObjectType *copy() = 0;
        virtual bool isEqual(ObjectType *type) = 0;
        virtual std::string toString() = 0;
        virtual ~ObjectType();
    };

    struct IntObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType *copy() override;
        bool isEqual(ObjectType *type) override;
        std::string toString() override;
        ~IntObject() override;
    };

    struct BoolObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType *copy() override;
        bool isEqual(ObjectType *type) override;
        std::string toString() override;
        ~BoolObject() override;
    };

    struct StringObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType *copy() override;
        bool isEqual(ObjectType *type) override;
        std::string toString() override;
        ~StringObject() override;
    };

    struct CharObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType * copy() override;
        bool isEqual(ObjectType *type) override;
        std::string toString() override;
        ~CharObject() override;
    };

    struct VoidObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType * copy() override;
        bool isEqual(ObjectType *type) override;
        std::string toString() override;
        ~VoidObject() override;
    };

    struct ArrayObject : public ObjectType {
        ObjectType *memberType;
        int memberNum;

        ArrayObject(ObjectType *memberType, int memberNum);
        SingleObjectType singleObjectType() override;
        ObjectType * copy() override;
        bool isEqual(ObjectType *type) override;
        std::string toString() override;
        ~ArrayObject() override;
    };

} // karl

#endif //KARL_OBJECT_TYPE_HPP
