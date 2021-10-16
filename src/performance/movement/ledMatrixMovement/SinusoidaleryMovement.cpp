#include "SinusoidaleryMovement.h"

namespace performer {

SinusoidaleryMovement::SinusoidaleryMovement(LedMatrixProxy &ledMatrix,
                                             impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          entitySpawner{},
          actionSpeed{0.5},
          maxEntities{500},
          mode{0} {

}

void SinusoidaleryMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    entitySpawner.handleIncomingPacket(packet);
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 13) {
            actionSpeed = morsel->value();
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
            float wobble = randomNumberGenerator.generateProportion();
            auto action = std::make_unique<SinusoidScatterAction>(ledMatrix, origin, color, actionSpeed,
                                                                  1, 2, wobble);
            actionCollection.addAction(move(action));
        }
        actionCollection.trimActions(maxEntities);
    }

}

void SinusoidaleryMovement::handleTick() {

}

}
