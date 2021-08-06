#include "Flash.h"

namespace performer {

Flash::Flash(LedMatrixProxy &ledMatrix, HSLColor color, int startIndex, int endIndex, float fadeRate)
        : LedMatrixAction{ledMatrix},
          color{color},
          startIndex{startIndex},
          endIndex{endIndex},
          fadeRate{fadeRate},
          shouldContinue{true} {

}

void Flash::execute() {
    auto fade = static_cast<int>(fadeRate * impresarioUtils::getElapsedTime(initialTimestamp) / 1000);
    auto lightness = color.getLightness() - fade;
    if (lightness < 0) {
        shouldContinue = false;
    } else {
        for (int index = startIndex; index <= endIndex; index++) {
            auto hue = color.getHue();
            hue += index;
            while (hue > HSL_HUE_MAX) {
                hue -= HSL_HUE_MAX;
            }
            ledMatrix[index] = HSLColor{hue, color.getSaturation(), static_cast<uint8_t>(lightness)};
        }
    }
}

bool Flash::finished() {
    return !shouldContinue;
}

void Flash::cleanup() {

}

}
