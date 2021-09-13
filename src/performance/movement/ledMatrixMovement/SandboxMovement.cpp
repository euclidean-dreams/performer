#include "SandboxMovement.h"

namespace performer {

SandboxMovement::SandboxMovement(performer::LedMatrixProxy &ledMatrix,
                                 impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator) {
}

void SandboxMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {

}

void SandboxMovement::handleTick() {
    for (int y = 0; y < ledMatrix.height(); y++) {
        for (int x = 0; x < ledMatrix.width(); x++) {
            auto hue = (tick / 7) % HSL_HUE_MAX;
            ledMatrix.setLed(x, y, HSLColor{static_cast<uint32_t>(hue), 100, 50});
        }
    }
}

}
