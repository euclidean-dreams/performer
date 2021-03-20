#ifndef PERFORMER_TIMELINE_H
#define PERFORMER_TIMELINE_H

#include <NonCopyable.h>
#include "event/Event.h"

namespace performer {

class Timeline : impresarioUtils::NonCopyable {
public:
    virtual ~Timeline() = default;

    virtual void addEvent(std::unique_ptr<const Event> event) = 0;
};

}

#endif //PERFORMER_TIMELINE_H
