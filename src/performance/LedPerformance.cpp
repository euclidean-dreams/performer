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

LedPerformance::LedPerformance(
        std::unique_ptr<std::vector<std::unique_ptr<impresarioUtils::PacketReceiver>>> packetReceivers,
        std::shared_ptr<LedMatrixProxy> ledMatrixProxy)
        : packetReceivers{move(packetReceivers)},
          ledMatrixProxy{move(ledMatrixProxy)},
          movements{},
          randomNumberGenerator{} {
    auto &ledMatrixProxyRef = *this->ledMatrixProxy;
    auto movement = std::make_unique<SandboxMovement>(ledMatrixProxyRef, randomNumberGenerator);
    movements.push_back(move(movement));
}

void LedPerformance::perform() {
    auto lock = ledMatrixProxy->acquireLock();
    handleIncomingPackets();
    conductMovements();
}

bool LedPerformance::finished() {
    return false;
}

void LedPerformance::handleIncomingPackets() {
    for (auto &packetReceiver: *packetReceivers) {
        auto packets = packetReceiver->receive();
        while (packets->morePacketsLeft()) {
            auto packet = packets->popPacket();
            for (auto &movement: movements) {
                movement->handleIncomingPacket(*packet);
            }
        }
    }
}

void LedPerformance::conductMovements() {
    for (auto &movement: movements) {
        movement->conduct();
    }
}

}
