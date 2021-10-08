#include "Circle.h"

namespace performer {

Circle::Circle(Coordinate origin, HSLColor rootColor, int radius)
        : Shape{origin, rootColor, calculateBoundingBox(origin, radius * 2, radius * 2)},
          radius{radius} {

}

bool Circle::coordinateInShape(Coordinate coordinate) {
    auto x = coordinate.x - origin.x;
    auto y = coordinate.y - origin.y;
    if (radius > x * x + y * y) {
        return true;
    }
    return false;
}

HSLColor Circle::calculateColor(Coordinate coordinate) {
    return rootColor;
}

void Circle::grow() {
    radius++;
    renderBounds = calculateBoundingBox(origin, radius * 2, radius * 2);
}

void Circle::shrink() {
    radius--;
    if (radius < 0) {
        radius = 0;
    }
    renderBounds = calculateBoundingBox(origin, radius * 2, radius * 2);
}

}
