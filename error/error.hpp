
#ifndef KARL_ERROR_HPP
#define KARL_ERROR_HPP

namespace karl {

    enum class ErrorType {
        LexError
    };

    void error(ErrorType type, int line, int column)

} // karl

#endif //KARL_ERROR_HPP
