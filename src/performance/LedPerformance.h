#ifndef PERFORMER_LEDPERFORMANCE_H
#define PERFORMER_LEDPERFORMANCE_H

#include <thread>
#include <zmq.hpp>
#include <ImpresarioUtils.h>
#include "performance/Performance.h"
#include "performance/movement/ledMatrixMovement/SandboxMovement.h"
#include "performance/movement/ledMatrixMovement/DisplaySignalMovement.h"
#include "performance/movement/ledMatrixMovement/FlameoHotmanMovement.h"
#include "performance/movement/ledMatrixMovement/RectanglandMovement.h"
#include "performance/movement/ledMatrixMovement/SinusoidaleryMovement.h"

namespace performer {

class LedPerformance : public Performance {
private:
    inline static const int TICK_INTERVAL_MICROSECONDS = 500;
    inline static const int CONDUCT_INTERVAL_MICROSECONDS = 2500;

    std::unique_ptr<std::vector<std::unique_ptr<impresarioUtils::PacketReceiver>>> packetReceivers;
    std::shared_ptr<LedMatrixProxy> ledMatrixProxy;
    std::vector<std::unique_ptr<Movement>> movements;
    impresarioUtils::RandomNumberGenerator randomNumberGenerator;
    uint64_t lastConduct;

public:
    static void startPerformanceLoop(std::unique_ptr<LedPerformance> ledPerformance);

    LedPerformance(std::unique_ptr<std::vector<std::unique_ptr<impresarioUtils::PacketReceiver>>> packetReceivers,
                   std::shared_ptr<LedMatrixProxy> ledMatrixProxy);

    void perform() override;

    bool finished() override;

    void handleIncomingPackets();

    void conductMovements();
};

}

#endif //PERFORMER_LEDPERFORMANCE_H
