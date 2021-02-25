#ifndef PERFORMER_RIPPLE_H
#define PERFORMER_RIPPLE_H

#include <memory>
#include "ledMatrix/LedMatrix.h"
#include "color/HSLColor.h"
#include "Action.h"

class Ripple : public Action {
private:
    LedMatrix &ledMatrix;
    int initialIndex;
    bool shouldContinue;
    HSLColor initialColor;
    float speed;

public:
    explicit Ripple(uint32_t initialTick, LedMatrix &ledMatrix, int initialIndex, HSLColor initialColor,
                    float speed);

    void execute(uint32_t tick) override;

    bool finished() override;
};

#endif //PERFORMER_RIPPLE_H
