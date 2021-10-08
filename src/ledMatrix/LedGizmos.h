#ifndef PERFORMER_LEDGIZMOS_H
#define PERFORMER_LEDGIZMOS_H

#include "ledMatrix/LedMatrixProxy.h"
#include "Coordinate.h"

namespace performer {

class LedGizmos {
public:
    static Coordinate calculateCoordinate(int index, LedMatrixProxy &ledMatrix);

    static Coordinate calculateCoordinateVertically(int index, LedMatrixProxy &ledMatrix);

    static uint32_t generateRandomHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    static uint32_t generateBoundedHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator, int min, int max);

    static uint32_t generateFrequencyBasedHue(int index, LedMatrixProxy &ledMatrix, int hueShift);

    static uint32_t generateFrequencyBasedHue(int index, LedMatrixProxy &ledMatrix, int minHue, int maxHue);

    static uint32_t generateSignificantlyDifferentHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                                      uint32_t originalHue, int significance);

    static uint32_t bindHue(int hue);

};

}

#endif //PERFORMER_LEDGIZMOS_H
