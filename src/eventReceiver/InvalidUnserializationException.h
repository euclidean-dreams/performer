#ifndef PERFORMER_INVALIDUNSERIALIZATIONEXCEPTION_H
#define PERFORMER_INVALIDUNSERIALIZATIONEXCEPTION_H

namespace performer {

class InvalidUnserializationException : public std::logic_error {
public:
    InvalidUnserializationException() : logic_error(
            "attempted to unserialize data using a type different than the one indicated by its identifier"
    ) {}
};

}

#endif //PERFORMER_INVALIDUNSERIALIZATIONEXCEPTION_H
