#include <performance/action/ledMatrixAction/RectangleGrowthAction.h>
#include "RectanglandMovement.h"

namespace performer {

RectanglandMovement::RectanglandMovement(LedMatrixProxy &ledMatrix,
                                         impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          entitySpawner{},
          entityGrowthSpeed{0.5},
          maxEntities{300} {

}

void RectanglandMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
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
            auto hueShift = (tick / 10) % HSL_HUE_MAX;
            auto hue = LedGizmos::generateFrequencyBasedHue(entityRadix.index, ledMatrix, hueShift);
            auto color = HSLColor{hue, 100, 50};
            auto width = randomNumberGenerator.generate(5);
            auto height = randomNumberGenerator.generate(5);
            auto action = std::make_unique<RectangleGrowthAction>(ledMatrix, origin, color, entityGrowthSpeed, width,
                                                                  height);
            actionCollection.addAction(move(action));
        }
        actionCollection.trimActions(maxEntities);
    }
}

void RectanglandMovement::handleTick() {

}

}
