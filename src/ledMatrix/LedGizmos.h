#ifndef PERFORMER_LEDGIZMOS_H
#define PERFORMER_LEDGIZMOS_H

#include "ledMatrix/LedMatrixProxy.h"
#include "Coordinate.h"

namespace performer {

class LedGizmos {
public:
    static Coordinate calculateCoordinate(int index, LedMatrixProxy &ledMatrix);

    static uint32_t generateRandomHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    static uint32_t generateFrequencyBasedHue(int index, LedMatrixProxy &ledMatrix, int hueShift);

    static uint32_t generateSignificantlyDifferentHue(impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                                      uint32_t originalHue, int significance);

};

}

#endif //PERFORMER_LEDGIZMOS_H
