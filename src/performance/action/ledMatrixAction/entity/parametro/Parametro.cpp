#include "Parametro.h"

namespace performer {

Parametro::Parametro(Coordinate origin, HSLColor rootColor)
        : Entity(origin, rootColor),
          currentTimeling{0} {

}

void Parametro::render(LedMatrixProxy &ledMatrix) {
    for (int timeling = 0; timeling < currentTimeling; timeling++) {
        auto coordinate = calculateCoordinate(timeling);
        if (ledMatrix.isValid(coordinate)) {
            ledMatrix.setLed({coordinate.x, coordinate.y}, calculateColor(coordinate));
        }
    }
}

void Parametro::advance() {
    currentTimeling++;
}

}
