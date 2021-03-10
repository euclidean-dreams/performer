#ifndef PERFORMER_EVENTRECEIVER_H
#define PERFORMER_EVENTRECEIVER_H

#include <vector>
#include <NonCopyable.h>
#include "eventReceiver/event/Event.h"

namespace performer {

class EventReceiver : impresarioUtils::NonCopyable {
public:
    virtual ~EventReceiver() = default;

    virtual std::unique_ptr<std::vector<std::unique_ptr<Event>>> receive() = 0;
};

}

#endif //PERFORMER_EVENTRECEIVER_H
