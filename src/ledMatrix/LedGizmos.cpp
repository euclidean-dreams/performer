#include "LedGizmos.h"

namespace performer {

Coordinate LedGizmos::calculateCoordinate(int index, LedMatrixProxy &ledMatrix) {
    auto x = index % ledMatrix.width();
    auto y = static_cast<int>(floor(index / ledMatrix.width()));
    return {x, y};
}

Coordinate LedGizmos::calculateCoordinateVertically(int index, LedMatrixProxy &ledMatrix) {
    auto x = static_cast<int>(floor(index / ledMatrix.height()));
    auto y = index % ledMatrix.height();
    return {x, y};
}

uint32_t LedGizmos::generateRandomHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator) {
    return randomNumberGenerator.generate(HSL_HUE_MAX);
}

uint32_t LedGizmos::generateFrequencyBasedHue(int index, LedMatrixProxy &ledMatrix, int hueShift) {
    auto hue = 300 * index / ledMatrix.size() + hueShift;
    return bindHue(hue);
}

uint32_t LedGizmos::generateFrequencyBasedHue(int index, LedMatrixProxy &ledMatrix, int minHue, int maxHue) {
    float normalizedPosition = static_cast<float>(index) / ledMatrix.size();
    auto unshiftedHue = normalizedPosition * (maxHue - minHue);
    auto hue = unshiftedHue + minHue;
    return bindHue(hue);
}

uint32_t LedGizmos::generateSignificantlyDifferentHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                                      uint32_t originalHue, int significance) {
    auto resultHue = originalHue + randomNumberGenerator.generate(HSL_HUE_MAX - significance) + significance;
    return bindHue(resultHue);
}

uint32_t LedGizmos::generateBoundedHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator, int min,
                                       int max) {
    while (min > max) {
        max += HSL_HUE_MAX;
    }
    auto resultHue = randomNumberGenerator.generateProportion() * (max - min) + min;
    return bindHue(resultHue);
}

uint32_t LedGizmos::bindHue(int hue) {
    while (hue > HSL_HUE_MAX) {
        hue -= HSL_HUE_MAX;
    }
    while (hue < 0) {
        hue += HSL_HUE_MAX;
    }
    return hue;
}

}
