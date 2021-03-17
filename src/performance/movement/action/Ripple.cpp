#include "Ripple.h"

namespace performer {

Ripple::Ripple(LedMatrixProxy &ledMatrix, int initialIndex, HSLColor initialColor, float speed)
        : ledMatrix{ledMatrix},
          initialIndex{initialIndex},
          initialColor{initialColor},
          speed{speed},
          shouldContinue{true} {

}

void Ripple::execute() {
    if (shouldContinue) {
        auto elapsedTime = impresarioUtils::getElapsedTime(initialTimestamp);
        auto rippleDistance = static_cast<int>(std::roundf(elapsedTime * speed / 1000));
        auto startIndex = initialIndex - rippleDistance;
        if (startIndex < 0) {
            startIndex = 0;
        }
        auto endIndex = initialIndex + rippleDistance;
        if (endIndex >= ledMatrix.size()) {
            endIndex = ledMatrix.size() - 1;
        }
        for (int index = startIndex; index <= endIndex; index++) {
            auto lightness = 50 - std::abs(index - initialIndex) * 3;
            auto saturation = 100 - std::abs(index - initialIndex) * 1;
            if (lightness < 0) {
                lightness = 0;
            }
            if (saturation < 0) {
                saturation = 0;
            }
            ledMatrix[index] = HSLColor{initialColor.getHue(), static_cast<uint8_t>(saturation), static_cast<uint8_t>(lightness)};
        }
        if (startIndex == 0 && endIndex == ledMatrix.size() - 1) {
            shouldContinue = false;
        }
    }
}

bool Ripple::finished() {
    return !shouldContinue;
}

}
