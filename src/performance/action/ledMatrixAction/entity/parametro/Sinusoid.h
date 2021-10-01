#ifndef PERFORMER_SINUSOID_H
#define PERFORMER_SINUSOID_H

#include "performance/action/ledMatrixAction/entity/parametro/Parametro.h"

namespace performer {

class Sinusoid : public Parametro {
private:
    float frequency;
    float phase;
    float spread;
    float xMultiplier;

protected:
    Coordinate calculateCoordinate(int timeling) override;

    HSLColor calculateColor(Coordinate coordinate) override;

public:
    Sinusoid(Coordinate origin, HSLColor rootColor, float frequency, float phase, float spread, float xMultiplier);
};

}

#endif //PERFORMER_SINUSOID_H
