#ifndef PERFORMER_LEDPERFORMANCE_H
#define PERFORMER_LEDPERFORMANCE_H

#include <memory>
#include <zmq.hpp>
#include "Utils.h"
#include "RandomNumberGenerator.h"
#include "Performance.h"
#include "eventReceiver/EventReceiver.h"
#include "movement/Movement.h"
#include "movement/RippleMovement.h"
#include "eventReceiver/OnsetReceiver.h"
#include "color/HSLColor.h"
#include "ledMatrix/LedMatrix.h"
#include "ledMatrix/LedMatrixProxy.h"

using namespace flatbuffers;

class LedPerformance : public Performance {
private:
    std::unique_ptr<NetworkSocket> ledPacketOutputSocket;
    vector<std::unique_ptr<EventReceiver>> eventReceivers;
    vector<std::unique_ptr<Movement>> movements;
    RandomNumberGenerator randomNumberGenerator;
    LedMatrixProxy ledMatrix;

public:
    explicit LedPerformance(std::unique_ptr<OnsetReceiver> onsetReceiver,
                            std::unique_ptr<NetworkSocket> ledPacketOutputSocket, uint ledCount);

    void perform() override;

    void handleEvents();

    void conductMovements();

    void sendLedPacket();
};

#endif //PERFORMER_LEDPERFORMANCE_H
