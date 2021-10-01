#include "LedGizmos.h"

namespace performer {

Coordinate LedGizmos::calculateCoordinate(int index, LedMatrixProxy &ledMatrix) {
    auto x = index % ledMatrix.width();
    auto y = static_cast<int>(floor(index / ledMatrix.width()));
    return {x, y};
}

uint32_t LedGizmos::generateRandomHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator) {
    return randomNumberGenerator.generate(HSL_HUE_MAX);
}

uint32_t LedGizmos::generateFrequencyBasedHue(int index, LedMatrixProxy &ledMatrix, int hueShift) {
    auto hue = 300 * index / ledMatrix.size() + hueShift;
    while (hue > HSL_HUE_MAX) {
        hue -= HSL_HUE_MAX;
    }
    while (hue < 0) {
        hue += HSL_HUE_MAX;
    }
    return hue;
}

uint32_t LedGizmos::generateSignificantlyDifferentHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                                      uint32_t originalHue, int significance) {
    auto resultHue = originalHue + randomNumberGenerator.generate(HSL_HUE_MAX - significance) + significance;
    while (resultHue > HSL_HUE_MAX) {
        resultHue -= HSL_HUE_MAX;
    }
    while (resultHue < 0) {
        resultHue += HSL_HUE_MAX;
    }
    return resultHue;
}

}
