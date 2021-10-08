#ifndef PERFORMER_FLAME_H
#define PERFORMER_FLAME_H

#include "ledMatrix/LedMatrixProxy.h"
#include "color/HSLColor.h"
#include "ledMatrix/Coordinate.h"
#include "ledMatrix/LedGizmos.h"
#include "performance/action/ledMatrixAction/entity/shape/Shape.h"

namespace performer {

class Flame : public Shape {
private:
    int width;
    int height;
    HSLColor initialColor;
    float flickerPhase;
    float flickerMagnitude;
    bool flickerPhaseDirection;
    bool flickerMagnitudeDirection;

protected:
    bool coordinateInShape(Coordinate coordinate) override;

    HSLColor calculateColor(Coordinate coordinate) override;

public:
    Flame(Coordinate origin, HSLColor rootColor, int width, int height);

    void grow() override;

    void shrink() override;

    void flicker(impresarioUtils::RandomNumberGenerator &randomNumberGenerator, float intensity);
};

}

#endif //PERFORMER_FLAME_H
