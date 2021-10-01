#include "SinusoidScatterAction.h"

namespace performer {

SinusoidScatterAction::SinusoidScatterAction(LedMatrixProxy &ledMatrix, Coordinate origin, HSLColor color, float speed,
                                             float frequency, float spread)
        : LedMatrixAction(ledMatrix),
          color{color},
          speed{speed} {
    rightWave = std::make_unique<Sinusoid>(origin, color, frequency, 1, spread, 1);
    leftWave = std::make_unique<Sinusoid>(origin, color, frequency, 1, spread, -1);
}

bool SinusoidScatterAction::finished() {
    return tick > 50;
}

void SinusoidScatterAction::handleTick() {
    if (tick % static_cast<int>(10 - 9 * speed) == 0) {
        rightWave->advance();
        leftWave->advance();
    }
    color = color.darken(1);
    rightWave->setRootColor(color);
    leftWave->setRootColor(color);
    rightWave->render(ledMatrix);
    leftWave->render(ledMatrix);
}

}
