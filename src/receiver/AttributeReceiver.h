#ifndef PERFORMER_ATTRIBUTERECEIVER_H
#define PERFORMER_ATTRIBUTERECEIVER_H

#include <vector>
#include "NetworkSocket.h"
#include "NonCopyable.h"
#include "event/Event.h"

class AttributeReceiver : NonCopyable {
protected:
    std::unique_ptr<NetworkSocket> inputSocket;

public:
    AttributeReceiver(std::unique_ptr<NetworkSocket> inputSocket);

    vector<Event> receive();

};

#endif //PERFORMER_ATTRIBUTERECEIVER_H
