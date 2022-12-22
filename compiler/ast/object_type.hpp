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
        ObjectType * copy() override;
        ~IntObject() override;
    };

    struct BoolObject : public ObjectType {

    };

} // karl

#endif //KARL_OBJECT_TYPE_HPP
