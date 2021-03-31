#ifndef PERFORMER_EVENTCOLLECTION_H
#define PERFORMER_EVENTCOLLECTION_H

#include <list>
#include <memory>
#include <ImpresarioUtils.h>
#include "event/Event.h"

namespace performer {

class EventCollection : impresarioUtils::NonCopyable {
private:
    std::list<std::unique_ptr<const Event>> events;

public:
    EventCollection();

    void pushEvent(std::unique_ptr<const Event> event);

    bool moreEventsLeft() const;

    std::unique_ptr<const Event> popEvent();
};

}

#endif //PERFORMER_EVENTCOLLECTION_H
