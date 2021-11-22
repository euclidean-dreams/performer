#ifndef PERFORMER_DRAGONARYMOVEMENT_H
#define PERFORMER_DRAGONARYMOVEMENT_H

#include "Bootstrapper.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/movement/ledMatrixMovement/EntitySpawner.h"
#include "performance/action/ledMatrixAction/DragonCurveTraceAction.h"
#include "ledMatrix/LedGizmos.h"
#include "ledMatrix/Coordinate.h"

namespace performer {

class DragonaryMovement : public LedMatrixMovement {
private:
    EntitySpawner entitySpawner;
    int maxEntities;
    int mode;
    int hue;
    float speed;

public:
    DragonaryMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleIncomingPacket(const impresarioUtils::Packet &packet) override;

    void handleTick() override;

};

}

#endif //PERFORMER_DRAGONARYMOVEMENT_H
