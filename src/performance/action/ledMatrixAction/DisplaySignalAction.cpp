#include "DisplaySignalAction.h"

namespace performer {

DisplaySignalAction::DisplaySignalAction(LedMatrixProxy &ledMatrix, std::unique_ptr<std::vector<float>> signal,
                                         float fadeRate, float movingAverage)
        : LedMatrixAction{ledMatrix},
          signal{move(signal)},
          fadeRate{fadeRate},
          movingAverage{movingAverage},
          invocations{0} {

}

void DisplaySignalAction::execute() {
    auto fade = static_cast<int>(fadeRate * impresarioUtils::getElapsedTime(initialTimestamp) / 1000);
    if (invocations == 0) {
        fade = 0;
    }
    uint32_t hue;
    uint8_t saturation;
    uint8_t lightness;
    for (int index = 0; index < ledMatrix.size(); index++) {
        auto sample = (*signal)[index];
        if (sample > 0) {
            hue = 240 - static_cast<int>(std::round(200 * sample / movingAverage));
            saturation = 50 + static_cast<int>(std::round(50 * sample / movingAverage));
            auto potentialLightness = static_cast<int>(std::round(50 * sample / movingAverage)) - fade;
            if (potentialLightness < 0) {
                potentialLightness = 0;
            }
            lightness = potentialLightness;
            ledMatrix[index] = HSLColor{hue, saturation, lightness};

        }
    }
}

bool DisplaySignalAction::finished() {
    return invocations > 5;
}

void DisplaySignalAction::cleanup() {

}

}
