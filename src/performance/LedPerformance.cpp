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

    // bass
    auto flashes = FlashOnOnsetMovement::createSymmetrical(ledMatrixProxyRef, randomNumberGenerator, timelineManager,
                                                           {ImpresarioSerialization::FrequencyBand::bass},
                                                           {270, 100, 50},
                                                           0, 29, 0.35);
    movements.push_back(move(flashes.first));
    movements.push_back(move(flashes.second));

    // snares
    flashes = FlashOnOnsetMovement::createSymmetrical(ledMatrixProxyRef, randomNumberGenerator, timelineManager,
                                                      {ImpresarioSerialization::FrequencyBand::brilliance},
                                                      {180, 100, 90},
                                                      30, 44, 0.35);
    movements.push_back(move(flashes.first));
    movements.push_back(move(flashes.second));

    // low mids
    flashes = FlashOnOnsetMovement::createSymmetrical(ledMatrixProxyRef, randomNumberGenerator, timelineManager,
                                                      {ImpresarioSerialization::FrequencyBand::lowMidrange},
                                                      {0, 100, 50},
                                                      45, 54, 0.35);
    movements.push_back(move(flashes.first));
    movements.push_back(move(flashes.second));

    // mids
    flashes = FlashOnOnsetMovement::createSymmetrical(ledMatrixProxyRef, randomNumberGenerator, timelineManager,
                                                      {ImpresarioSerialization::FrequencyBand::midrange},
                                                      {40, 100, 50},
                                                      55, 64, 0.35);
    movements.push_back(move(flashes.first));
    movements.push_back(move(flashes.second));

    // high mids
    flashes = FlashOnOnsetMovement::createSymmetrical(ledMatrixProxyRef, randomNumberGenerator, timelineManager,
                                                      {ImpresarioSerialization::FrequencyBand::upperMidrange},
                                                      {110, 100, 50},
                                                      65, 74, 0.35);
    movements.push_back(move(flashes.first));
    movements.push_back(move(flashes.second));

    // highs
    flashes = FlashOnOnsetMovement::createSymmetrical(ledMatrixProxyRef, randomNumberGenerator, timelineManager,
                                                      {ImpresarioSerialization::FrequencyBand::presence},
                                                      {65, 100, 50},
                                                      75, 90, 0.35);
    movements.push_back(move(flashes.first));
    movements.push_back(move(flashes.second));

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
