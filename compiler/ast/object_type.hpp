#ifndef KARL_OBJECT_TYPE_HPP
#define KARL_OBJECT_TYPE_HPP

namespace karl {

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
        virtual ~ObjectType() = 0;
    };

    struct IntObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType *copy() override;
        ~IntObject() override;
    };

    struct BoolObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType *copy() override;
        ~BoolObject() override;
    };

    struct StringObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType *copy() override;
        ~StringObject() override;
    };

    struct CharObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType * copy() override;
        ~CharObject() override;
    };

    struct VoidObject : public ObjectType {
        SingleObjectType singleObjectType() override;
        ObjectType * copy() override;
        ~VoidObject() override;
    };

    struct ArrayObject : public ObjectType {
        ObjectType *memberType;
        int memberNum;

        ArrayObject(ObjectType *memberType, int memberNum);
        SingleObjectType singleObjectType() override;
        ObjectType * copy() override;
        ~ArrayObject() override;
    };

} // karl

#endif //KARL_OBJECT_TYPE_HPP
