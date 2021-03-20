#ifndef PERFORMER_MOVEMENT_H
#define PERFORMER_MOVEMENT_H

#include <NonCopyable.h>
#include "event/Event.h"

namespace performer {

class Movement : impresarioUtils::NonCopyable {
protected:
    static const int MAX_ONSET_LATENCY = 10000;

public:
    virtual ~Movement() = default;

    virtual void handleEvent(const Event &event) = 0;

    virtual void conduct() = 0;
};

}

#endif //PERFORMER_MOVEMENT_H
