#ifndef PERFORMER_EVENTRECEIVER_H
#define PERFORMER_EVENTRECEIVER_H

#include <NetworkSocket.h>
#include <NonCopyable.h>
#include "Event.h"
#include "eventReceiver/EventCollection.h"

namespace performer {

class EventReceiver : impresarioUtils::NonCopyable {
private:
    std::unique_ptr<impresarioUtils::NetworkSocket> input;

public:
    explicit EventReceiver(std::unique_ptr<impresarioUtils::NetworkSocket> input);

    std::unique_ptr<EventCollection> receive();
};

}

#endif //PERFORMER_EVENTRECEIVER_H
