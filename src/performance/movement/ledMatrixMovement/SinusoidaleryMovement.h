#ifndef PERFORMER_SINUSOIDALERYMOVEMENT_H
#define PERFORMER_SINUSOIDALERYMOVEMENT_H

#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/movement/ledMatrixMovement/EntitySpawner.h"
#include "ledMatrix/LedGizmos.h"
#include "performance/action/ledMatrixAction/SinusoidScatterAction.h"

namespace performer {

class SinusoidaleryMovement : public LedMatrixMovement {
private:
    EntitySpawner entitySpawner;
    float actionSpeed;
    int maxEntities;
    int mode;

public:
    SinusoidaleryMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleIncomingPacket(const impresarioUtils::Packet &packet) override;

    void handleTick() override;
};

}

#endif //PERFORMER_SINUSOIDALERYMOVEMENT_H
