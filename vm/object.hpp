#ifndef KARL_OBJECT_HPP
#define KARL_OBJECT_HPP

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

    struct Object {
        virtual SingleObjectType type() = 0;
        virtual ~Object() = 0;
    };

    struct

} // karl

#endif //KARL_OBJECT_HPP
