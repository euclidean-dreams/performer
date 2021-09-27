#ifndef PERFORMER_DISPLAYSIGNALMOVEMENT_H
#define PERFORMER_DISPLAYSIGNALMOVEMENT_H

#include "Bootstrapper.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/action/ledMatrixAction/DisplaySignalAction.h"

namespace performer {

class DisplaySignalMovement : public LedMatrixMovement {
private:
    int hue;
    std::vector<float> previousDisplaySignal;

    // color change
    uint64_t lastColorChangeTimestamp;
    uint64_t minimumTimeBetweenColorChanges;
    float energyRequiredForColorChangeMultiplier;

    float sampleModifierAlpha;
    float sampleModifierBeta;

    int doctorHue(const std::vector<float> &displaySignal);

    std::unique_ptr<std::vector<float>> calculateDisplaySignal(const impresarioUtils::Packet &packet);

    std::unique_ptr<std::vector<float>> addDerivative(const std::vector<float> &inputSignal);

public:
    DisplaySignalMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleIncomingPacket(const impresarioUtils::Packet &packet) override;

    void handleTick() override;
};

}

#endif //PERFORMER_DISPLAYSIGNALMOVEMENT_H
