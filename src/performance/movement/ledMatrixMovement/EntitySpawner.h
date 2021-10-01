#ifndef PERFORMER_ENTITYSPAWNER_H
#define PERFORMER_ENTITYSPAWNER_H

#include <ImpresarioUtils.h>
#include "ledMatrix/Coordinate.h"

namespace performer {

struct EntityRadix {
    int index;
    float magnitude;
};

class EntitySpawner {
private:
    float normalizationScalingFactor;
    float effectThreshold;

public:
    EntitySpawner();

    void handleIncomingPacket(const impresarioUtils::Packet &packet);

    std::unique_ptr<std::vector<EntityRadix>> calculateRadixes(const flatbuffers::Vector<float> *samples);

};

}

#endif //PERFORMER_ENTITYSPAWNER_H
