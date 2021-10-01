#ifndef PERFORMER_RECTANGLANDMOVEMENT_H
#define PERFORMER_RECTANGLANDMOVEMENT_H

#include "Bootstrapper.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/movement/ledMatrixMovement/EntitySpawner.h"
#include "ledMatrix/LedGizmos.h"
#include "performance/action/ledMatrixAction/RectangleGrowthAction.h"
#include "ledMatrix/Coordinate.h"

namespace performer {

class RectanglandMovement : public LedMatrixMovement {
private:
    EntitySpawner entitySpawner;
    float actionGrowthSpeed;
    int maxTotalRipples;

public:
    RectanglandMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleIncomingPacket(const impresarioUtils::Packet &packet) override;

    void handleTick() override;

};

}

#endif //PERFORMER_RECTANGLANDMOVEMENT_H
