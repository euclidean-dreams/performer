#include "Beat.h"

Beat::Beat(uint32_t initialTick, LedMatrix &ledMatrix, int startIndex, int endIndex, HSLColor color)
        : Action{initialTick},
          ledMatrix{ledMatrix},
          startIndex{startIndex},
          endIndex{endIndex},
          color{color},
          shouldContinue{true} {

}

void Beat::execute(uint32_t tick) {
    for (int index = startIndex; index < endIndex; index++) {
        ledMatrix.modifyLed(index, color);
    }
    if (tick - initialTick > 20) {
        shouldContinue = false;
    }
}

bool Beat::finished() {
    return !shouldContinue;
}
