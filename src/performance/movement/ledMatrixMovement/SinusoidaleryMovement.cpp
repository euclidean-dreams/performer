#include "SinusoidaleryMovement.h"

namespace performer {

SinusoidaleryMovement::SinusoidaleryMovement(LedMatrixProxy &ledMatrix,
                                             impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          entitySpawner{},
          actionSpeed{0.5},
          maxEntities{500} {

}

void SinusoidaleryMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    entitySpawner.handleIncomingPacket(packet);
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 13) {
            actionSpeed = morsel->value();
        }
    }
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::displaySignal) {
        auto rawDisplaySignal = packet.getDisplaySignal();
        auto signal = rawDisplaySignal->samples();
        auto entityRadixes = entitySpawner.calculateRadixes(signal);
        for (auto entityRadix: *entityRadixes) {
            auto origin = LedGizmos::calculateCoordinate(entityRadix.index, ledMatrix);
            auto hue = LedGizmos::generateRandomHue(randomNumberGenerator);
            auto color = HSLColor{hue, 100, 50};
            auto action = std::make_unique<SinusoidScatterAction>(ledMatrix, origin, color, actionSpeed,
                                                                  1, 2);
            actionCollection.addAction(move(action));
        }
        actionCollection.trimActions(maxEntities);
    }

}

void SinusoidaleryMovement::handleTick() {

}

}
