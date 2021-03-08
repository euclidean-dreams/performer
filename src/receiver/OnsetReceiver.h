#ifndef PERFORMER_ONSETRECEIVER_H
#define PERFORMER_ONSETRECEIVER_H

#include <zmq.hpp>
#include "AttributeReceiver.h"

class OnsetReceiver: public AttributeReceiver {
public:
    OnsetReceiver create(context_t context, const string &inputEndpoint);

    OnsetReceiver();
};

#endif //PERFORMER_ONSETRECEIVER_H
