#ifndef PERFORMER_CLOUDSPACEMOVEMENT_H
#define PERFORMER_CLOUDSPACEMOVEMENT_H

#include "Bootstrapper.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/movement/ledMatrixMovement/EntitySpawner.h"
#include "ledMatrix/LedGizmos.h"
#include "ledMatrix/Coordinate.h"

namespace performer {

class CloudSpaceMovement : public LedMatrixMovement {
private:
    EntitySpawner entitySpawner;
    float entityGrowthSpeed;
    int maxEntities;

public:
    CloudSpaceMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleIncomingPacket(const impresarioUtils::Packet &packet) override;

    void handleTick() override;
};

}

#endif //PERFORMER_CLOUDSPACEMOVEMENT_H
