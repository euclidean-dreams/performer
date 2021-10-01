#include "RectangleGrowthAction.h"

namespace performer {

RectangleGrowthAction::RectangleGrowthAction(LedMatrixProxy &ledMatrix, Coordinate origin, HSLColor color,
                                             float growthSpeed, int width, int height)
        : LedMatrixAction(ledMatrix),
          color{color},
          growthSpeed{growthSpeed} {
    shape = std::make_unique<Rectangle>(origin, color, width, height);
}

bool RectangleGrowthAction::finished() {
    return tick > 120;
}

void RectangleGrowthAction::handleTick() {
    if (tick % static_cast<int>(100 - 99 * growthSpeed) == 0) {
        shape->grow();
        color = color.darken(1);
    }
    shape->setRootColor(color);
    shape->render(ledMatrix);
}

}
