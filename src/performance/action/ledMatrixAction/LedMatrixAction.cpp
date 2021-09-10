#include "LedMatrixAction.h"

namespace performer {

LedMatrixAction::LedMatrixAction(LedMatrixProxy &ledMatrix)
        : ledMatrix{ledMatrix},
          initialTimestamp{impresarioUtils::getCurrentTime()} {

}

}
