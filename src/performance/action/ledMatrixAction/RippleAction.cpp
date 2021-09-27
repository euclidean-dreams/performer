#include "RippleAction.h"

namespace performer {

RippleAction::RippleAction(LedMatrixProxy &ledMatrix, HSLColor color, int originX, int originY, float rippleSpeed)
        : LedMatrixAction(ledMatrix),
          color{color},
          originX{originX},
          originY{originY},
          rippleSpeed{rippleSpeed} {

}

bool RippleAction::finished() {
    return tick > 500;
}

void RippleAction::handleTick() {
    double radius = calculateRadius();
    auto minX = originX - radius;
    if (minX < 0) {
        minX = 0;
    }
    auto maxX = originX + radius;
    if (maxX >= ledMatrix.width()) {
        maxX = ledMatrix.width() - 1;
    }
    auto minY = originY - radius;
    if (minY < 0) {
        minY = 0;
    }
    auto maxY = originY + radius;
    if (maxY >= ledMatrix.height()) {
        maxY = ledMatrix.height() - 1;
    }
    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            ledMatrix.setLed(x, y, color);
        }
    }
}

double RippleAction::calculateRadius() const {
    auto radius = floor(tick / 15 * rippleSpeed);
    return radius;
}

}
