#include "WorshipMovement.h"

namespace performer {

WorshipMovement::WorshipMovement(LedMatrixProxy &ledMatrix,
                                           impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          entitySpawner{},
          maxEntities{30},
          hue{0},
          mode{0} {

}

void WorshipMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    entitySpawner.handleIncomingPacket(packet);
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 13) {
            hue = morsel->value() * HSL_HUE_MAX;
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
                color = HSLColor{LedGizmos::bindHue(currentHue), 100, 40};
            } else if (mode == 2) {
                color = HSLColor{LedGizmos::bindHue(randomNumberGenerator.generate(HSL_HUE_MAX)), 100, 40};
            }
            auto width = entityRadix.magnitude * 10 + 20;
            auto height = entityRadix.magnitude * 10 + 4;
            auto action = std::make_unique<FlameAction>(ledMatrix, randomNumberGenerator, origin, color, width, height,
                                                        mode);
            actionCollection.addAction(move(action));
        }
        actionCollection.trimActions(maxEntities);
    }
}

void WorshipMovement::handleTick() {

}

}
