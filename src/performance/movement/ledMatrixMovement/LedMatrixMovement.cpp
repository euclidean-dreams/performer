#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"

namespace performer {

LedMatrixMovement::LedMatrixMovement(LedMatrixProxy &ledMatrix,
                                     impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : ledMatrix{ledMatrix},
          randomNumberGenerator{randomNumberGenerator},
          actionCollection{},
          tick{0} {

}

void LedMatrixMovement::conduct() {
    actionCollection.executeActions();
    handleTick();
    tick++;
}

}
