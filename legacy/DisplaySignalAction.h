#ifndef PERFORMER_DISPLAYSIGNALACTION_H
#define PERFORMER_DISPLAYSIGNALACTION_H

#include "performance/action/ledMatrixAction/LedMatrixAction.h"

namespace performer {

class DisplaySignalAction : public LedMatrixAction {
private:
    std::unique_ptr<std::vector<float>> signal;
    float fadeRate;
    int invocations;
    float movingAverage;

public:
    DisplaySignalAction(LedMatrixProxy &ledMatrix, std::unique_ptr<std::vector<float>> signal, float fadeRate,
                        float movingAverage);

    void execute() override;

    bool finished() override;

    void cleanup() override;

};

}

#endif //PERFORMER_DISPLAYSIGNALACTION_H
