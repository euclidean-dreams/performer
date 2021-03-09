#ifndef PERFORMER_ONSETRECEIVER_H
#define PERFORMER_ONSETRECEIVER_H

#include <zmq.hpp>
#include "Config.h"
#include "EventReceiver.h"
#include "event/OnsetEvent.h"

using namespace ImpresarioSerialization;

class OnsetReceiver : public EventReceiver {
private:
    std::unique_ptr<NetworkSocket> inputSocket;

public:
    static std::unique_ptr<OnsetReceiver> create(context_t &context, const string &inputEndpoint);

    explicit OnsetReceiver(std::unique_ptr<NetworkSocket> inputSocket);

    std::unique_ptr<vector<std::unique_ptr<Event>>> receive() override;
};

#endif //PERFORMER_ONSETRECEIVER_H
