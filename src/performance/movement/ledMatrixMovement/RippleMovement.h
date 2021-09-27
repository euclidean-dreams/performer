#ifndef PERFORMER_RIPPLEMOVEMENT_H
#define PERFORMER_RIPPLEMOVEMENT_H

#include "Bootstrapper.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/action/ledMatrixAction/RippleAction.h"

namespace performer {

class RippleMovement : public LedMatrixMovement {
private:
    std::vector<float> previousDisplaySignal;
    float previousSumEnergyDelta;
    float effectThreshold;
    float rippleSpeed;
    int maxTotalRipples;

    std::unique_ptr<std::vector<std::tuple<int, int>>> calculateRippleOrigins(
            const flatbuffers::Vector<float> *samples);

public:
    RippleMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleIncomingPacket(const impresarioUtils::Packet &packet) override;

    void handleTick() override;

};

}

#endif //PERFORMER_RIPPLEMOVEMENT_H
