#include "DisplaySignalAction.h"

namespace performer {

DisplaySignalAction::DisplaySignalAction(LedMatrixProxy &ledMatrix, std::unique_ptr<std::vector<float>> signal,
                                         uint32_t hue, float lightnessMultiplier, float maxLightness)
        : LedMatrixAction{ledMatrix},
          signal{move(signal)},
          hue{hue},
          lightnessMultiplier{lightnessMultiplier},
          maxLightness{maxLightness} {

}

bool DisplaySignalAction::finished() {
    return false;
}

void DisplaySignalAction::handleTick() {
    for (int y = 0; y < ledMatrix.height(); y++) {
        for (int x = 0; x < ledMatrix.width(); x++) {
            auto displaySignalIndex = y * ledMatrix.width() + x;
            float lightness = (*signal)[displaySignalIndex] * lightnessMultiplier;
            if (lightness > maxLightness) {
                lightness = maxLightness;
            }
            if (ledMatrix.isValid({x, y})) {
                ledMatrix.setLed({x, y}, HSLColor{hue, 100, static_cast<uint8_t>(lightness)});
            }
        }
    }
}

}
