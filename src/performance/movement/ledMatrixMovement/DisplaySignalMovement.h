#ifndef PERFORMER_DISPLAYSIGNALMOVEMENT_H
#define PERFORMER_DISPLAYSIGNALMOVEMENT_H

#include "Bootstrapper.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/action/ledMatrixAction/DisplaySignalAction.h"

namespace performer {

class DisplaySignalMovement : public LedMatrixMovement {
private:
    std::list<float> logMovingAverageValues;
    std::list<float> logSumValues;
    std::list<float> logMovingAverageValues2;
    std::list<float> powerMovingAverageValues;
    float powerTransparencyThreshold;
    std::vector<float> lastDisplaySignal;
    int lastHue;

public:
    DisplaySignalMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                          const TimelineManager &timelineManager);

    void handleEvent(const Event &event) override;

};

}

#endif //PERFORMER_DISPLAYSIGNALMOVEMENT_H
