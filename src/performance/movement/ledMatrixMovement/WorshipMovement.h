#ifndef PERFORMER_WORSHIPMOVEMENT_H
#define PERFORMER_WORSHIPMOVEMENT_H

#include "Bootstrapper.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/movement/ledMatrixMovement/EntitySpawner.h"
#include "performance/action/ledMatrixAction/FlameAction.h"
#include "ledMatrix/LedGizmos.h"
#include "ledMatrix/Coordinate.h"

namespace performer {

class WorshipMovement : public LedMatrixMovement {
private:
    EntitySpawner entitySpawner;
    int maxEntities;
    int hue;
    int mode;

public:
    WorshipMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleIncomingPacket(const impresarioUtils::Packet &packet) override;

    void handleTick() override;

};

}

#endif //PERFORMER_WORSHIPMOVEMENT_H
