#include "Shape.h"

namespace performer {

Shape::Shape(Coordinate origin, HSLColor rootColor, BoundingBox renderBounds)
        : Entity{origin, rootColor},
          renderBounds{renderBounds} {

}

void Shape::render(LedMatrixProxy &ledMatrix) {
    auto minX = renderBounds.lowerLeft.x;
    if (minX < 0) {
        minX = 0;
    }
    auto minY = renderBounds.lowerLeft.y;
    if (minY < 0) {
        minY = 0;
    }
    auto maxX = renderBounds.upperRight.x;
    if (maxX >= ledMatrix.width()) {
        maxX = ledMatrix.width() - 1;
    }
    auto maxY = renderBounds.upperRight.y;
    if (maxY >= ledMatrix.height()) {
        maxY = ledMatrix.height() - 1;
    }
    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (ledMatrix.isValid({x, y})) {
                if (coordinateInShape({x, y})) {
                    ledMatrix.setLed({x, y}, calculateColor({x, y}));
                }
            }
        }
    }
}

BoundingBox Shape::calculateBoundingBox(Coordinate origin, int width, int height) {
    auto minX = origin.x - width / 2;
    auto maxX = origin.x + width / 2;
    auto minY = origin.y - height / 2;
    auto maxY = origin.y + height / 2;
    Coordinate lowerLeft = {minX, minY};
    Coordinate upperRight = {maxX, maxY};
    return {lowerLeft, upperRight};
}

}
