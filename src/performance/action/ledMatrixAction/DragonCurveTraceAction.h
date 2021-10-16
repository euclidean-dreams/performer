#ifndef PERFORMER_DRAGONCURVETRACEACTION_H
#define PERFORMER_DRAGONCURVETRACEACTION_H

#include "performance/action/ledMatrixAction/entity/lindogram/DragonCurve.h"
#include "ledMatrix/Coordinate.h"
#include "performance/action/ledMatrixAction/LedMatrixAction.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class DragonCurveTraceAction : public LedMatrixAction {
private:
    float speed;
    std::unique_ptr<Lindogram> entity;
    float currentLightness;

public:
    DragonCurveTraceAction(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                           Coordinate origin, HSLColor color, float speed, double scale);

    bool finished() override;

    void handleTick() override;
};

}

#endif //PERFORMER_DRAGONCURVETRACEACTION_H
