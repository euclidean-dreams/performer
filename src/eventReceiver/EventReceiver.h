#ifndef PERFORMER_EVENTRECEIVER_H
#define PERFORMER_EVENTRECEIVER_H

#include <vector>
#include "NetworkSocket.h"
#include "NonCopyable.h"
#include "event/Event.h"

class EventReceiver : NonCopyable {
public:
    virtual ~EventReceiver() = default;

    virtual std::unique_ptr<vector<std::unique_ptr<Event>>> receive() = 0;
};

#endif //PERFORMER_EVENTRECEIVER_H
