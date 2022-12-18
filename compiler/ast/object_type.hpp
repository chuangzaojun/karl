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
    };

} // karl

#endif //KARL_OBJECT_TYPE_HPP
