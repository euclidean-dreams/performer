#include <performance/action/ledMatrixAction/RectangleGrowthAction.h>
#include "RectanglandMovement.h"

namespace performer {

RectanglandMovement::RectanglandMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          entitySpawner{},
          actionGrowthSpeed{0.5},
          maxTotalRipples{500} {

}

void RectanglandMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    entitySpawner.handleIncomingPacket(packet);
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 13) {
            actionGrowthSpeed = morsel->value();
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
            auto action = std::make_unique<RectangleGrowthAction>(ledMatrix, origin, color, actionGrowthSpeed, width,
                                                                  height);
            actionCollection.addAction(move(action));
        }
        actionCollection.trimActions(maxTotalRipples);
    }
}

void RectanglandMovement::handleTick() {

}

}
