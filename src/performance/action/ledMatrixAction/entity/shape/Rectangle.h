#ifndef PERFORMER_RECTANGLE_H
#define PERFORMER_RECTANGLE_H

#include "ledMatrix/LedMatrixProxy.h"
#include "color/HSLColor.h"
#include "ledMatrix/Coordinate.h"
#include "performance/action/ledMatrixAction/entity/shape/Shape.h"

namespace performer {

class Rectangle : public Shape {
private:
    int width;
    int height;

protected:
    bool coordinateInShape(Coordinate coordinate) override;

    HSLColor calculateColor(Coordinate coordinate) override;

public:
    Rectangle(Coordinate origin, HSLColor rootColor, int width, int height);

    void grow() override;

    void shrink() override;

};

}

#endif //PERFORMER_RECTANGLE_H
