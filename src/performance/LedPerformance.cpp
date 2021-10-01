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
          randomNumberGenerator{},
          lastConduct{0} {
    auto &ledMatrixProxyRef = *this->ledMatrixProxy;
//    auto movement = std::make_unique<SandboxMovement>(ledMatrixProxyRef, randomNumberGenerator);
    auto movement = std::make_unique<SinusoidaleryMovement>(ledMatrixProxyRef, randomNumberGenerator);
    movements.push_back(move(movement));
}

void LedPerformance::perform() {
    auto lock = ledMatrixProxy->acquireLock();
    handleIncomingPackets();
    if (impresarioUtils::getElapsedTime(lastConduct) > CONDUCT_INTERVAL_MICROSECONDS) {
        ledMatrixProxy->clear();
        conductMovements();
        lastConduct = impresarioUtils::getCurrentTime();
    }
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
            if (packet->getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
                auto morsel = packet->getFloatMorsel();
                if (morsel->field() == 14) {
                    ledMatrixProxy->setBrightness(morsel->value() * Config::getInstance().getMaxBrightness());
                } else if (morsel->field() == 100) {
                    movements.clear();
                    auto movement = std::make_unique<RectanglandMovement>(*this->ledMatrixProxy,
                                                                          randomNumberGenerator);
                    movements.push_back(move(movement));
                } else if (morsel->field() == 101) {
                    movements.clear();
                    auto movement = std::make_unique<SinusoidaleryMovement>(*this->ledMatrixProxy,
                                                                            randomNumberGenerator);
                    movements.push_back(move(movement));
                }
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
