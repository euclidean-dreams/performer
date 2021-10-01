#include "Shape.h"

namespace performer {

Shape::Shape(Coordinate origin, HSLColor rootColor, BoundingBox renderBounds)
        : Entity{origin, rootColor},
          renderBounds{renderBounds} {

}

void Shape::render(LedMatrixProxy &ledMatrix) {
    for (int y = renderBounds.lowerLeft.y; y <= renderBounds.upperRight.y; y++) {
        for (int x = renderBounds.lowerLeft.x; x < renderBounds.upperRight.x; x++) {
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
