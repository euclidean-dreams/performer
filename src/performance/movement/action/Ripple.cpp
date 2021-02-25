#include "Ripple.h"

Ripple::Ripple(uint32_t initialTick, LedMatrix &ledMatrix, int initialIndex, HSLColor initialColor, float speed)
        : Action{initialTick},
          ledMatrix{ledMatrix},
          initialIndex{initialIndex},
          shouldContinue{true},
          initialColor{initialColor},
          speed{speed} {

}

void Ripple::execute(uint32_t tick) {
    if (shouldContinue) {
        auto distanceFromCenter = static_cast<int>(roundf(static_cast<float>(tick - initialTick) * speed));
        auto startIndex = initialIndex - distanceFromCenter;
        if (startIndex < 0) {
            startIndex = 0;
        }
        auto endIndex = initialIndex + distanceFromCenter;
        if (endIndex >= ledMatrix.getLedCount()) {
            endIndex = ledMatrix.getLedCount() - 1;
        }
        for (int index = startIndex; index <= endIndex; index++) {
            ledMatrix.modifyLed(index, initialColor);
        }
        if (startIndex == 0 && endIndex == ledMatrix.getLedCount() - 1) {
            shouldContinue = false;
        }
    }
}

bool Ripple::finished() {
    return !shouldContinue;
}
