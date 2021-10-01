#include "Sinusoid.h"

namespace performer {

Sinusoid::Sinusoid(Coordinate origin, HSLColor rootColor, float frequency, float phase, float spread, float xMultiplier)
        : Parametro(origin, rootColor),
          frequency{frequency},
          phase{phase},
          spread{spread},
          xMultiplier{xMultiplier} {

}

Coordinate Sinusoid::calculateCoordinate(int timeling) {
    auto x = xMultiplier * timeling;
    auto y = spread * sin(timeling / frequency + phase);
    return {static_cast<int>(x + origin.x), static_cast<int>(y) + origin.y};
}

HSLColor Sinusoid::calculateColor(Coordinate coordinate) {
    return rootColor;
}

}
