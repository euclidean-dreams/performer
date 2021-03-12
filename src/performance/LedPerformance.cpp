#include "LedPerformance.h"

namespace performer {

LedPerformance::LedPerformance(std::unique_ptr<OnsetReceiver> onsetReceiver,
                               std::unique_ptr<impresarioUtils::NetworkSocket> ledPacketOutputSocket, uint ledCount)
        : ledPacketOutputSocket{move(ledPacketOutputSocket)},
          eventReceivers{},
          movements{},
          randomNumberGenerator{},
          ledMatrix{ledCount} {
    eventReceivers.push_back(move(onsetReceiver));
    auto rippleMovement = std::make_unique<RippleMovement>(ledMatrix, randomNumberGenerator);
    movements.push_back(move(rippleMovement));
}

void LedPerformance::perform() {
    handleEvents();
    conductMovements();
    sendLedPacket();
    std::this_thread::sleep_for(std::chrono::microseconds(PERFORMANCE_WAKE_INTERVAL));
}

void LedPerformance::handleEvents() {
    for (auto &receiver: eventReceivers) {
        auto events = receiver->receive();
        for (auto &event: *events) {
            for (auto &movement: movements) {
                movement->handleEvent(*event);
            }
        }
    }
}

void LedPerformance::conductMovements() {
    for (auto &movement: movements) {
        movement->conduct();
    }
}

void LedPerformance::sendLedPacket() {
    auto a = ledPacketOutputSocket->receive(zmq::recv_flags::dontwait);
    if (!a->empty()) {
        auto ledPacket = ledMatrix.generateLedPacket();
        zmq::multipart_t message{ledPacket->GetBufferPointer(), ledPacket->GetSize()};
        ledPacketOutputSocket->send(message);
    }
}

}
