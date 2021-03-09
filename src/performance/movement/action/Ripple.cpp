#include "Ripple.h"

Ripple::Ripple(LedMatrixProxy &ledMatrix, int initialIndex, Color::HSLColor initialColor, float speed)
        : ledMatrix{ledMatrix},
          initialIndex{initialIndex},
          initialColor{initialColor},
          speed{speed},
          shouldContinue{true} {

}

void Ripple::execute() {
    if (shouldContinue) {
        auto rippleDistance = static_cast<int>(round(getElapsedTime(initialTimestamp) * speed / 1000));
        auto startIndex = initialIndex - rippleDistance;
        if (startIndex < 0) {
            startIndex = 0;
        }
        auto endIndex = initialIndex + rippleDistance;
        if (endIndex >= ledMatrix.size()) {
            endIndex = ledMatrix.size() - 1;
        }
        for (int index = startIndex; index <= endIndex; index++) {
            ledMatrix.modifyLed(index, initialColor);
        }
        if (startIndex == 0 && endIndex == ledMatrix.size() - 1) {
            shouldContinue = false;
        }
    }
}

bool Ripple::finished() {
    return !shouldContinue;
}
