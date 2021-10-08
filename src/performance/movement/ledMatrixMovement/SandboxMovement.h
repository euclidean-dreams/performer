#ifndef PERFORMER_SANDBOXMOVEMENT_H
#define PERFORMER_SANDBOXMOVEMENT_H

#include <ImpresarioUtils.h>
#include <ImpresarioSerialization.h>
#include <performance/action/ledMatrixAction/entity/shape/Flame.h>
#include "Config.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"

namespace performer {

class SandboxMovement : public LedMatrixMovement {
private:
    int x;
    int y;
    std::vector<std::unique_ptr<Flame>> flameStack;

public:
    SandboxMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleIncomingPacket(const impresarioUtils::Packet &packet) override;

    void handleTick() override;
};

}
#endif //PERFORMER_SANDBOXMOVEMENT_H
