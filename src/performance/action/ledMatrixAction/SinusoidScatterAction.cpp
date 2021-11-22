#include "SinusoidScatterAction.h"

namespace performer {

SinusoidScatterAction::SinusoidScatterAction(LedMatrixProxy &ledMatrix,
                                             impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                             Coordinate origin, HSLColor color, float speed,
                                             float frequency, float spread, int mode)
        : LedMatrixAction(ledMatrix),
          randomNumberGenerator{randomNumberGenerator},
          speed{speed} {
    auto sinusoidCount = 4;
    auto wobble = 0.4;
    for (int index = 0; index < sinusoidCount; index++) {
        int hue = 0;
        if (mode == 0) {
            hue = color.getHue() + index * 10;
        } else if (mode == 1) {
            hue = color.getHue() + index * 20 + randomNumberGenerator.generate(30);
        } else if (mode == 2) {
            hue = randomNumberGenerator.generate(HSL_HUE_MAX);
        }
        auto currentColor = HSLColor{LedGizmos::bindHue(hue), color.getSaturation(), color.getLightness()};
        sinusoids.push_back(std::make_unique<Sinusoid>(origin, currentColor, frequency, 1, spread, 1, wobble));
        wobble += 0.2 / sinusoidCount;
    }
}

bool SinusoidScatterAction::finished() {
    return tick > 50;
}

void SinusoidScatterAction::handleTick() {
    if (tick % static_cast<int>(10 - 9 * speed) == 0) {
        for (auto &sinusoid: sinusoids) {
            sinusoid->advance();
        }
    }
    for (auto &sinusoid: sinusoids) {
        auto color = sinusoid->getRootColor().darken(1);
        sinusoid->setRootColor(color);
        sinusoid->render(ledMatrix);
    }
}

}
