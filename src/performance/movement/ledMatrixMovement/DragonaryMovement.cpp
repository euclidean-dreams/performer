#include "DragonaryMovement.h"

namespace performer {

DragonaryMovement::DragonaryMovement(LedMatrixProxy &ledMatrix,
                                     impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          entitySpawner{},
          maxEntities{50},
          hue{0},
          mode{1},
          speed{0.1} {

}

void DragonaryMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    entitySpawner.handleIncomingPacket(packet);
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 13) {
            hue = morsel->value() * HSL_HUE_MAX;
        } else if (morsel->field() == 14) {
            speed = morsel->value();
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
                auto subHue = LedGizmos::bindHue(currentHue + entityRadix.index / 10);
                color = HSLColor{subHue, 100, 40};
            } else if (mode == 2) {
                color = HSLColor{LedGizmos::bindHue(randomNumberGenerator.generate(HSL_HUE_MAX)), 100, 40};
            }
            double scale = entityRadix.magnitude;
            auto action = std::make_unique<DragonCurveTraceAction>(ledMatrix, randomNumberGenerator, origin, color,
                                                                   speed, scale);
            actionCollection.addAction(move(action));
        }
        actionCollection.trimActions(maxEntities);
    }
}

void DragonaryMovement::handleTick() {

}

}
