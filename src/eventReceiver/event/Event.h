#ifndef PERFORMER_EVENT_H
#define PERFORMER_EVENT_H

#include "NonCopyable.h"

class Event : NonCopyable {
public:
    virtual ~Event() = default;
};

#endif //PERFORMER_EVENT_H
