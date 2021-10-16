#include "CloudSpaceMovement.h"

namespace performer {

CloudSpaceMovement::CloudSpaceMovement(LedMatrixProxy &ledMatrix,
                                       impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          entitySpawner{},
          entityGrowthSpeed{0.5},
          maxEntities{300} {

}

void CloudSpaceMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    entitySpawner.handleIncomingPacket(packet);
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 13) {
            entityGrowthSpeed = morsel->value();
        }
    }
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::displaySignal) {
        auto rawDisplaySignal = packet.getDisplaySignal();
        auto signal = rawDisplaySignal->samples();
        auto entityRadixes = entitySpawner.calculateRadixes(signal);
        for (auto entityRadix: *entityRadixes) {
            auto origin = LedGizmos::calculateCoordinate(entityRadix.index, ledMatrix);
            auto hue = (tick / 10) % HSL_HUE_MAX;
            auto color = HSLColor{LedGizmos::bindHue(hue), 100, 50};
            auto radius = entityRadix.magnitude * 10 + 20;
//            auto action = std::make_unique<CloudFloatAction>(ledMatrix, origin, color, entityGrowthSpeed, radius);
//            actionCollection.addAction(move(action));
        }
        actionCollection.trimActions(maxEntities);
    }
}

void CloudSpaceMovement::handleTick() {

}

}
