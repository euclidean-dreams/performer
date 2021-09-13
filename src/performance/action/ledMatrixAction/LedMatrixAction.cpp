#include "LedMatrixAction.h"

namespace performer {

LedMatrixAction::LedMatrixAction(LedMatrixProxy &ledMatrix)
        : ledMatrix{ledMatrix},
          initialTimestamp{impresarioUtils::getCurrentTime()},
          tick{0} {

}

void LedMatrixAction::execute() {
    handleTick();
    tick++;
}

}
