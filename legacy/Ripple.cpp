#include "Ripple.h"

namespace performer {

performer::Ripple::Ripple(performer::LedMatrixProxy &ledMatrix, performer::HSLColor color, int startIndex, float speed)
        : LedMatrixAction(ledMatrix),
          color{color},
          startIndex{startIndex},
          speed{speed},
          shouldContinue{true} {

}

void performer::Ripple::execute() {
    auto elapsedTime = static_cast<float>(impresarioUtils::getElapsedTime(initialTimestamp));
    auto fade = static_cast<int>(speed * elapsedTime / 10000);
    auto baseLightness = color.getLightness() - fade / 2;
    if (baseLightness > 0) {
        auto spread = fade * 2;
        auto lowIndex = startIndex - spread;
        if (lowIndex < 0) {
            lowIndex = 0;
        }
        auto highIndex = startIndex + spread;
        if (highIndex >= ledMatrix.size()) {
            highIndex = ledMatrix.size() - 1;
        }
        for (int index = lowIndex; index <= highIndex; index++) {
            auto indexLightness = baseLightness - std::abs(startIndex - index) / 100;
            if (indexLightness < 0) {
                indexLightness = 0;
            }
            ledMatrix[index] = HSLColor{color.getHue(), 100, static_cast<uint8_t>(indexLightness)};
        }
    } else {
        shouldContinue = false;
    }
}

bool performer::Ripple::finished() {
    return !shouldContinue;
}

void performer::Ripple::cleanup() {

}

}
