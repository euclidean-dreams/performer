#include "EntitySpawner.h"

namespace performer {

EntitySpawner::EntitySpawner()
        : normalizationScalingFactor{0.5},
          effectThreshold{0.5} {

}

void EntitySpawner::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 11) {
            normalizationScalingFactor = morsel->value();
        } else if (morsel->field() == 12) {
            effectThreshold = morsel->value();
        }
    }
}

std::unique_ptr<std::vector<EntityRadix>> EntitySpawner::calculateRadixes(const flatbuffers::Vector<float> *samples) {
    auto result = std::make_unique<std::vector<EntityRadix>>();
    for (int index = 0; index < samples->size(); index++) {
        auto sample = (*samples)[index];

        // accommodate for crazy large last sample - this will go once those ridiculous triangular filters are changed
        if (index == samples->size() - 1) {
            sample /= 100;
        }

        // normalize
        sample = 1 - 1 / (std::pow(sample / (-1 * (1000 - 1000 * normalizationScalingFactor)), 2) + 1);

        if (sample > 1 - effectThreshold) {
            result->push_back({index, sample});
        }
    }
    return result;
}

}
