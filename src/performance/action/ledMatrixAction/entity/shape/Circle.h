#ifndef PERFORMER_CIRCLE_H
#define PERFORMER_CIRCLE_H

#include "ledMatrix/LedMatrixProxy.h"
#include "color/HSLColor.h"
#include "ledMatrix/Coordinate.h"
#include "performance/action/ledMatrixAction/entity/shape/Shape.h"

namespace performer {

class Circle : public Shape {
private:
    int radius;

protected:
    bool coordinateInShape(Coordinate coordinate) override;

    HSLColor calculateColor(Coordinate coordinate) override;

public:
    Circle(Coordinate origin, HSLColor rootColor, int radius);

    void grow() override;

    void shrink() override;
};

}

#endif //PERFORMER_CIRCLE_H
