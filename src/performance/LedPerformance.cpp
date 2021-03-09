#include "LedPerformance.h"

LedPerformance::LedPerformance(std::unique_ptr<OnsetReceiver> onsetReceiver,
                               std::unique_ptr<NetworkSocket> ledPacketOutputSocket, uint ledCount)
        : ledPacketOutputSocket{move(ledPacketOutputSocket)},
          eventReceivers{},
          movements{},
          randomNumberGenerator{},
          ledMatrix{ledCount} {
    eventReceivers.push_back(move(onsetReceiver));
    auto rippleMovement = make_unique<RippleMovement>(ledMatrix, randomNumberGenerator);
    movements.push_back(move(rippleMovement));
}

void LedPerformance::perform() {
    handleEvents();
    conductMovements();
    sendLedPacket();
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
    auto a = ledPacketOutputSocket->receive(recv_flags::dontwait);
    if (!a->empty()) {
        FlatBufferBuilder builder{};
        vector<ImpresarioSerialization::RGBColor> leds;
        for (int i = 0; i < ledMatrix.size(); i++) {
            auto color = ledMatrix[i];
            auto serializedColor = ImpresarioSerialization::RGBColor(color.getRed(), color.getGreen(), color.getBlue());
            leds.push_back(serializedColor);
        }
        auto serializedLeds = builder.CreateVectorOfStructs(leds);
        auto ledPacket = CreateLedPacket(builder, serializedLeds);
        builder.Finish(ledPacket);
        multipart_t message{builder.GetBufferPointer(), builder.GetSize()};
        ledPacketOutputSocket->send(message);
    }
}

