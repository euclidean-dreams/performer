#ifndef PERFORMER_DISPLAYSIGNALACTION_H
#define PERFORMER_DISPLAYSIGNALACTION_H

#include <memory>
#include <vector>
#include "performance/action/ledMatrixAction/LedMatrixAction.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class DisplaySignalAction : public LedMatrixAction {
private:
    std::unique_ptr<std::vector<float>> signal;
    uint32_t hue;
    float lightnessMultiplier;
    float maxLightness;

public:
    DisplaySignalAction(LedMatrixProxy &ledMatrix, std::unique_ptr<std::vector<float>> signal,
                        uint32_t hue, float lightnessMultiplier, float maxLightness);

    bool finished() override;

    void handleTick() override;
};

}

#endif //PERFORMER_DISPLAYSIGNALACTION_H
