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
                               std::shared_ptr<LedMatrixProxy> ledMatrixProxy,
                               std::unique_ptr<impresarioUtils::NetworkSocket> morselSocket)
        : eventReceiver{move(eventReceiver)},
          ledMatrixProxy{move(ledMatrixProxy)},
          movements{},
          randomNumberGenerator{},
          timelineManager{} {
    auto &ledMatrixProxyRef = *this->ledMatrixProxy;
    auto displaySignalMovement = std::make_unique<DisplaySignalMovement>(
            ledMatrixProxyRef, randomNumberGenerator, timelineManager, move(morselSocket)
    );
    movements.push_back(move(displaySignalMovement));

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
        timelineManager.addEvent(move(event));
    }
}

void LedPerformance::conductMovements() {
    for (auto &movement: movements) {
        movement->conduct();
    }
}

}
