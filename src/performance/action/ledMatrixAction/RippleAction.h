#ifndef PERFORMER_RIPPLEMOVEMENT_H
#define PERFORMER_RIPPLEACTION_H

#include <memory>
#include <vector>
#include "performance/action/ledMatrixAction/LedMatrixAction.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class RippleAction : public LedMatrixAction {
private:
    HSLColor color;
    int originX;
    int originY;
    float rippleSpeed;

public:
    RippleAction(LedMatrixProxy &ledMatrix, HSLColor color, int originX, int originY, float rippleSpeed);

    bool finished() override;

    void handleTick() override;

    double calculateRadius() const;
};

}

#endif //PERFORMER_RIPPLEMOVEMENT_H
