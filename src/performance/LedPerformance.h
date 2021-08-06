#ifndef PERFORMER_LEDPERFORMANCE_H
#define PERFORMER_LEDPERFORMANCE_H

#include <thread>
#include <zmq.hpp>
#include <ImpresarioUtils.h>
#include "event/EventReceiver.h"
#include "performance/Performance.h"
#include "performance/timeline/TimelineManager.h"
#include "performance/movement/LoggingMovement.h"
#include "performance/movement/ledMatrixMovement/FlashOnOnsetMovement.h"
#include "performance/movement/ledMatrixMovement/DisplaySignalMovement.h"

namespace performer {

class LedPerformance : public Performance {
private:
    inline static const int TICK_INTERVAL_MICROSECONDS = 500;

    std::unique_ptr<EventReceiver> eventReceiver;
    std::shared_ptr<LedMatrixProxy> ledMatrixProxy;
    std::vector<std::unique_ptr<Movement>> movements;
    impresarioUtils::RandomNumberGenerator randomNumberGenerator;
    TimelineManager timelineManager;

public:
    static void startPerformanceLoop(std::unique_ptr<LedPerformance> ledPerformance);

    LedPerformance(std::unique_ptr<EventReceiver> eventReceiver, std::shared_ptr<LedMatrixProxy> ledMatrixProxy);

    void perform() override;

    bool finished() override;

    void handleEvents();

    void conductMovements();
};

}

#endif //PERFORMER_LEDPERFORMANCE_H
