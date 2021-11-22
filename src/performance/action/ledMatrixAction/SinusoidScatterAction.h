#ifndef PERFORMER_SINUSOIDSCATTERACTION_H
#define PERFORMER_SINUSOIDSCATTERACTION_H

#include "performance/action/ledMatrixAction/entity/parametro/Sinusoid.h"
#include "performance/action/ledMatrixAction/LedMatrixAction.h"
#include "ledMatrix/LedMatrixProxy.h"
#include "ledMatrix/LedGizmos.h"

namespace performer {

class SinusoidScatterAction : public LedMatrixAction {
private:
    float speed;
    std::vector<std::unique_ptr<Parametro>> sinusoids;
    impresarioUtils::RandomNumberGenerator &randomNumberGenerator;

public:
    SinusoidScatterAction(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                          Coordinate origin, HSLColor color, float speed, float frequency,
                          float spread, int mode);

    bool finished() override;

    void handleTick() override;
};

}

#endif //PERFORMER_SINUSOIDSCATTERACTION_H
