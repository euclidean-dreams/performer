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
    auto &ledMatrixProxyRef = *this->ledMatrixProxy;
    auto freq = std::vector<ImpresarioSerialization::FrequencyBand>{ImpresarioSerialization::FrequencyBand::all};
    auto frequencyBands = std::make_unique<std::vector<ImpresarioSerialization::FrequencyBand>>(freq);
    auto color = HSLColor{65, 100, 50};
    auto flasher = std::make_unique<FlashOnOnsetMovement>(ledMatrixProxyRef, randomNumberGenerator, timelineManager,
                                                          move(frequencyBands), color, 0, Bootstrapper::LED_COUNT, 0.5);
    movements.push_back(move(flasher));

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
