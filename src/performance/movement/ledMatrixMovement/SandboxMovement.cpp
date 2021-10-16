#include <spdlog/spdlog.h>
#include "SandboxMovement.h"

namespace performer {

SandboxMovement::SandboxMovement(performer::LedMatrixProxy &ledMatrix,
                                 impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          x{0},
          y{0} {
    auto color = HSLColor{50, 100, 50};
    stacky.push_back(
            std::make_unique<DragonCurve>(Coordinate{10, 5}, color, 0, 15, 1)
    );
}

void SandboxMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {

}

void SandboxMovement::handleTick() {
    for (auto &entity: stacky) {
        entity->tick();
        entity->tick();
        entity->tick();
    }
    for (auto &entity: stacky) {
        entity->render(ledMatrix);
    }
}

}
