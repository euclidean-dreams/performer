#ifndef PERFORMER_RIPPLE_H
#define PERFORMER_RIPPLE_H

#include <cmath>
#include <Time.h>
#include "ledMatrix/LedMatrixProxy.h"
#include "performance/movement/action/Action.h"

namespace performer {

class Ripple : public Action {
private:
    LedMatrixProxy &ledMatrix;
    int initialIndex;
    HSLColor initialColor;
    float speed;
    bool shouldContinue;

public:
    Ripple(LedMatrixProxy &ledMatrix, int initialIndex, HSLColor initialColor, float speed);

    void execute() override;

    bool finished() override;
};

}

#endif //PERFORMER_RIPPLE_H
