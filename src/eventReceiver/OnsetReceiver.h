#ifndef PERFORMER_ONSETRECEIVER_H
#define PERFORMER_ONSETRECEIVER_H

#include <zmq.hpp>
#include <NetworkSocket.h>
#include "Config.h"
#include "eventReceiver/EventReceiver.h"
#include "eventReceiver/event/OnsetEvent.h"

namespace performer {

class OnsetReceiver : public EventReceiver {
private:
    std::unique_ptr<impresarioUtils::NetworkSocket> inputSocket;

public:
    static std::unique_ptr<OnsetReceiver> create(zmq::context_t &context, const std::string &inputEndpoint);

    explicit OnsetReceiver(std::unique_ptr<impresarioUtils::NetworkSocket> inputSocket);

    std::unique_ptr<std::vector<std::unique_ptr<Event>>> receive() override;
};

}

#endif //PERFORMER_ONSETRECEIVER_H
