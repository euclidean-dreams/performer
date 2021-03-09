#ifndef PERFORMER_RIPPLE_H
#define PERFORMER_RIPPLE_H

#include "Utils.h"
#include "ledMatrix/LedMatrixProxy.h"
#include "Action.h"

class Ripple : public Action {
private:
    LedMatrixProxy &ledMatrix;
    int initialIndex;
    Color::HSLColor initialColor;
    float speed;
    bool shouldContinue;

public:
    Ripple(LedMatrixProxy &ledMatrix, int initialIndex, Color::HSLColor initialColor, float speed);

    void execute() override;

    bool finished() override;
};

#endif //PERFORMER_RIPPLE_H
