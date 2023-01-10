#ifndef KARL_OBJECT_HPP
#define KARL_OBJECT_HPP

namespace karl::vm {

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

} // karl

#endif //KARL_OBJECT_HPP
