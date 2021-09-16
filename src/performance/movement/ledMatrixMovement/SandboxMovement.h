#ifndef PERFORMER_SANDBOXMOVEMENT_H
#define PERFORMER_SANDBOXMOVEMENT_H

#include <ImpresarioUtils.h>
#include <ImpresarioSerialization.h>
#include "Config.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"

namespace performer {

class SandboxMovement : public LedMatrixMovement {
private:
    int x;
    int y;

public:
    SandboxMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleIncomingPacket(const impresarioUtils::Packet &packet) override;

    void handleTick() override;
};

}
#endif //PERFORMER_SANDBOXMOVEMENT_H
