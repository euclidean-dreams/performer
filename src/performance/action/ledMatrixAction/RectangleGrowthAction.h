#ifndef PERFORMER_RECTANGLANDMOVEMENT_H
#define PERFORMER_RIPPLEACTION_H

#include "performance/action/ledMatrixAction/entity/shape/Rectangle.h"
#include "ledMatrix/Coordinate.h"
#include "performance/action/ledMatrixAction/LedMatrixAction.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class RectangleGrowthAction : public LedMatrixAction {
private:
    HSLColor color;
    float growthSpeed;
    std::unique_ptr<Shape> shape;

public:
    RectangleGrowthAction(LedMatrixProxy &ledMatrix, Coordinate origin, HSLColor color, float growthSpeed, int width,
                          int height);

    bool finished() override;

    void handleTick() override;
};

}

#endif //PERFORMER_RECTANGLANDMOVEMENT_H
