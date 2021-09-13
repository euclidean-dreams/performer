#ifndef PERFORMER_DISPLAYSIGNALMOVEMENT_H
#define PERFORMER_DISPLAYSIGNALMOVEMENT_H

#include "Bootstrapper.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/action/ledMatrixAction/DisplaySignalAction.h"
#include "performance/action/ledMatrixAction/Ripple.h"

namespace performer {

class DisplaySignalMovement : public LedMatrixMovement {
private:
    std::vector<float> previousDisplaySignal;
    uint32_t baseHue;
    std::unique_ptr<impresarioUtils::NetworkSocket> morselSocket;
    float baseLightnessMultiplier;
    float lightnessMultiplier;
    float floatingParameter;
    uint64_t lastColorChangeTimestamp;
    uint64_t minimumTimeBetweenColorChanges;
    int mode;
    int highestSampleIndex;
    uint64_t lastActionTimestamp;

public:
    DisplaySignalMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                          const TimelineManager &timelineManager,
                          std::unique_ptr<impresarioUtils::NetworkSocket> morselSocket);

    void handleEvent(const Event &event) override;

    uint32_t getNewHue(uint32_t initialHue);
};

}

#endif //PERFORMER_DISPLAYSIGNALMOVEMENT_H
