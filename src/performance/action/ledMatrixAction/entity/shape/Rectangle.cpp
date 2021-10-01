#include "Rectangle.h"

namespace performer {

Rectangle::Rectangle(Coordinate origin, HSLColor rootColor, int width, int height)
        : Shape{origin, rootColor, calculateBoundingBox(origin, width, height)},
          width{width},
          height{height} {

}

bool Rectangle::coordinateInShape(Coordinate coordinate) {
    auto minX = origin.x - width / 2;
    auto maxX = origin.x + width / 2;
    auto minY = origin.y - height / 2;
    auto maxY = origin.y + height / 2;
    if (coordinate.x >= minX && coordinate.x <= maxX) {
        if (coordinate.y >= minY && coordinate.y <= maxY) {
            return true;
        }
    }
    return false;
}

HSLColor Rectangle::calculateColor(Coordinate coordinate) {
    return rootColor;
}

void Rectangle::grow() {
    width++;
    height++;
    renderBounds = calculateBoundingBox(origin, width, height);
}

void Rectangle::shrink() {
    width--;
    height--;
    if (width < 0) {
        width = 0;
    }
    if (height < 0) {
        height = 0;
    }
    renderBounds = calculateBoundingBox(origin, width, height);
}

}
