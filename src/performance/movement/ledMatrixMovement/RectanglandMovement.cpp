#include <performance/action/ledMatrixAction/RectangleGrowthAction.h>
#include "RectanglandMovement.h"

namespace performer {

RectanglandMovement::RectanglandMovement(LedMatrixProxy &ledMatrix,
                                         impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          entitySpawner{},
          entityGrowthSpeed{0.5},
          maxEntities{300},
          hue{0},
          mode{1} {

}

void RectanglandMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    entitySpawner.handleIncomingPacket(packet);
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 13) {
            hue = morsel->value() * HSL_HUE_MAX;
        } else if (morsel->field() == 14) {
            entityGrowthSpeed = morsel->value();
        } else if (morsel->field() == 100) {
            mode = 0;
        } else if (morsel->field() == 101) {
            mode = 1;
        } else if (morsel->field() == 102) {
            mode = 2;
        }
    }
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::displaySignal) {
        auto rawDisplaySignal = packet.getDisplaySignal();
        auto signal = rawDisplaySignal->samples();
        auto entityRadixes = entitySpawner.calculateRadixes(signal);
        for (auto entityRadix: *entityRadixes) {
            auto origin = LedGizmos::calculateCoordinate(entityRadix.index, ledMatrix);
            int currentHue = hue + randomNumberGenerator.generate(5);
            HSLColor color = {0, 0, 0};
            if (mode == 0) {
                auto hueShift = (tick / 10) % HSL_HUE_MAX;
                auto subHue = LedGizmos::generateFrequencyBasedHue(entityRadix.index, ledMatrix, hueShift);
                color = HSLColor{subHue, 100, 50};
            } else if (mode == 1) {
                auto subHue = LedGizmos::bindHue(currentHue + entityRadix.index / 5);
                color = HSLColor{subHue, 100, 40};
            } else if (mode == 2) {
                color = HSLColor{LedGizmos::bindHue(randomNumberGenerator.generate(HSL_HUE_MAX)), 100, 40};
            }
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
