#include "DragonaryMovement.h"

namespace performer {

DragonaryMovement::DragonaryMovement(LedMatrixProxy &ledMatrix,
                                     impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          entitySpawner{},
          maxEntities{100},
          mode{0},
          speed{0.1} {

}

void DragonaryMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    entitySpawner.handleIncomingPacket(packet);
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 13) {
            speed = morsel->value();
        } else if (morsel->field() == 100) {
            mode = 0;
        } else if (morsel->field() == 101) {
            mode = 1;
        }
    }
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::displaySignal) {
        auto rawDisplaySignal = packet.getDisplaySignal();
        auto signal = rawDisplaySignal->samples();
        auto entityRadixes = entitySpawner.calculateRadixes(signal);
        for (auto entityRadix: *entityRadixes) {
            auto origin = LedGizmos::calculateCoordinate(entityRadix.index, ledMatrix);
            HSLColor color = {0, 0, 0};
            if (mode == 0) {
                auto hueShift = (tick / 10) % HSL_HUE_MAX;
                int hue = LedGizmos::generateFrequencyBasedHue(entityRadix.index, ledMatrix, hueShift);
                hue += randomNumberGenerator.generate(30) - 15;
                color = HSLColor{LedGizmos::bindHue(hue), 100, 50};
            } else if (mode == 1) {
                color = HSLColor{LedGizmos::bindHue(randomNumberGenerator.generate(HSL_HUE_MAX)), 100, 50};
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
