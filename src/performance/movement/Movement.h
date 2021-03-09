#ifndef PERFORMER_MOVEMENT_H
#define PERFORMER_MOVEMENT_H

#include "eventReceiver/event/Event.h"
#include "NonCopyable.h"

class Movement : NonCopyable {
public:
    virtual ~Movement() = default;

    virtual void handleEvent(const Event &event) = 0;

    virtual void conduct() = 0;
};

#endif //PERFORMER_MOVEMENT_H
