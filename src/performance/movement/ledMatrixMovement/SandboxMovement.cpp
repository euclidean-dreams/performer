#include <spdlog/spdlog.h>
#include "SandboxMovement.h"

namespace performer {

SandboxMovement::SandboxMovement(performer::LedMatrixProxy &ledMatrix,
                                 impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          x{0},
          y{0} {
    for (int index = 0; index < 3; index++) {
        auto color = HSLColor{10, 100, static_cast<uint8_t>(30 + 10 * index)};
        auto height = 10 - index;
        auto width = 7 - index;
        flameStack.push_back(
                std::make_unique<Flame>(Coordinate{10, 4}, color, width, height)
        );
    }
}

void SandboxMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {

}

void SandboxMovement::handleTick() {
    for (auto &flame: flameStack) {
        flame->render(ledMatrix);
        if (tick % 15 == 0) {
            flame->flicker(randomNumberGenerator, 1);
        }
    }
}

}
