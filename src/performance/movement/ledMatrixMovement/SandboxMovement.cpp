#include <spdlog/spdlog.h>
#include "SandboxMovement.h"

namespace performer {

SandboxMovement::SandboxMovement(performer::LedMatrixProxy &ledMatrix,
                                 impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          x{0},
          y{0} {
}

void SandboxMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {

}

void SandboxMovement::handleTick() {
//    ledMatrix.clear();
//    auto hue = (tick / 7) % HSL_HUE_MAX;
//    ledMatrix.setLed(x, y, HSLColor{static_cast<uint32_t>(hue), 100, 50});
//    if (tick % 10 == 0) {
//        x++;
//        if (x == ledMatrix.width()) {
//            x = 0;
//            y++;
//            if (y == ledMatrix.height()) {
//                y = 0;
//            }
//        }
//    }
    for (int y = 0; y < ledMatrix.height(); y++) {
        for (int x = 0; x < ledMatrix.width(); x++) {
            ledMatrix.setLed(x, y, HSLColor{static_cast<uint32_t>(100), 100, 50});
        }
    }
}

}
