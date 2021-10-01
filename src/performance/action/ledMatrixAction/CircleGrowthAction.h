#ifndef PERFORMER_CIRCLEGROWTHACTION_H
#define PERFORMER_CIRCLEGROWTHACTION_H

#include "performance/action/ledMatrixAction/entity/shape/Circle.h"
#include "ledMatrix/Coordinate.h"
#include "performance/action/ledMatrixAction/LedMatrixAction.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class CircleGrowthAction : public LedMatrixAction {
private:
    float growthSpeed;
    std::unique_ptr<Shape> shape;
    std::unique_ptr<Shape> outline;

public:
    CircleGrowthAction(LedMatrixProxy &ledMatrix, Coordinate origin, HSLColor color, float growthSpeed);

    bool finished() override;

    void handleTick() override;
};

}

#endif //PERFORMER_CIRCLEGROWTHACTION_H
