#include "CircleGrowthAction.h"

namespace performer {

CircleGrowthAction::CircleGrowthAction(LedMatrixProxy &ledMatrix, Coordinate origin, HSLColor color,
                                       float growthSpeed)
        : LedMatrixAction(ledMatrix),
          growthSpeed{growthSpeed} {
    shape = std::make_unique<Circle>(origin, color, 2);
}

bool CircleGrowthAction::finished() {
    return tick > 300;
}

void CircleGrowthAction::handleTick() {
    if (tick % static_cast<int>(25 - 24 * growthSpeed) == 0) {
        shape->grow();
    }
    shape->render(ledMatrix);
}

}
