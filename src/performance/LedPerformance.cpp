#include "LedPerformance.h"

namespace performer {

void LedPerformance::startPerformanceLoop(std::unique_ptr<LedPerformance> ledPerformance) {
    while (!ledPerformance->finished()) {
        auto cycleStartTime = impresarioUtils::getCurrentTime();
        ledPerformance->perform();
        auto totalCycleTime = impresarioUtils::getElapsedTime(cycleStartTime);
        if (TICK_INTERVAL_MICROSECONDS > totalCycleTime) {
            std::this_thread::sleep_for(
                    std::chrono::microseconds(TICK_INTERVAL_MICROSECONDS - totalCycleTime)
            );
        }
    }
}

LedPerformance::LedPerformance(std::unique_ptr<EventReceiver> eventReceiver,
                               std::shared_ptr<LedMatrixProxy> ledMatrixProxy)
        : eventReceiver{move(eventReceiver)},
          ledMatrixProxy{move(ledMatrixProxy)},
          movements{},
          randomNumberGenerator{},
          timelineManager{} {
    auto rippleMovement = std::make_unique<RippleMovement>(*this->ledMatrixProxy, randomNumberGenerator,
                                                           timelineManager);
    movements.push_back(move(rippleMovement));
//    auto pitchTrackingMovement = std::make_unique<PitchTrackingMovement>(*this->ledMatrixProxy, timelineManager);
//    movements.push_back(move(pitchTrackingMovement));
//    auto loggingMovement = std::make_unique<LoggingMovement>();
//    movements.push_back(move(loggingMovement));
}

void LedPerformance::perform() {
    auto lock = ledMatrixProxy->acquireLock();
    handleEvents();
    conductMovements();
}

bool LedPerformance::finished() {
    return false;
}

void LedPerformance::handleEvents() {
    auto events = eventReceiver->receive();
    while (events->moreEventsLeft()) {
        auto event = events->popEvent();
        for (auto &movement: movements) {
            movement->handleEvent(*event);
        }
        timelineManager.pushEvent(move(event));
    }
}

void LedPerformance::conductMovements() {
    for (auto &movement: movements) {
        movement->conduct();
    }
}

}
