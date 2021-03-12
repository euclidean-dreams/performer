#ifndef PERFORMER_LEDPERFORMANCE_H
#define PERFORMER_LEDPERFORMANCE_H

#include <thread>
#include <zmq.hpp>
#include <NetworkSocket.h>
#include <RandomNumberGenerator.h>
#include "eventReceiver/OnsetReceiver.h"
#include "performance/Performance.h"
#include "performance/movement/RippleMovement.h"

namespace performer {

class LedPerformance : public Performance {
private:
    std::unique_ptr<impresarioUtils::NetworkSocket> ledPacketOutputSocket;
    std::vector<std::unique_ptr<EventReceiver>> eventReceivers;
    std::vector<std::unique_ptr<Movement>> movements;
    impresarioUtils::RandomNumberGenerator randomNumberGenerator;
    LedMatrixProxy ledMatrix;

public:
    explicit LedPerformance(std::unique_ptr<OnsetReceiver> onsetReceiver,
                            std::unique_ptr<impresarioUtils::NetworkSocket> ledPacketOutputSocket, uint ledCount);

    void perform() override;

    void handleEvents();

    void conductMovements();

    void sendLedPacket();
};

}

#endif //PERFORMER_LEDPERFORMANCE_H
