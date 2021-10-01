#ifndef PERFORMER_SINUSOIDSCATTERACTION_H
#define PERFORMER_SINUSOIDSCATTERACTION_H

#include "performance/action/ledMatrixAction/entity/parametro/Sinusoid.h"
#include "performance/action/ledMatrixAction/LedMatrixAction.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class SinusoidScatterAction : public LedMatrixAction {
private:
    HSLColor color;
    float speed;
    std::unique_ptr<Parametro> rightWave;
    std::unique_ptr<Parametro> leftWave;

public:
    SinusoidScatterAction(LedMatrixProxy &ledMatrix, Coordinate origin, HSLColor color, float speed, float frequency,
                          float spread);

    bool finished() override;

    void handleTick() override;
};

}

#endif //PERFORMER_SINUSOIDSCATTERACTION_H
