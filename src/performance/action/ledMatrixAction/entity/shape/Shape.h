#ifndef PERFORMER_SHAPE_H
#define PERFORMER_SHAPE_H

#include "performance/action/ledMatrixAction/entity/Entity.h"

namespace performer {

struct BoundingBox {
    Coordinate lowerLeft;
    Coordinate upperRight;
};

class Shape : public Entity {
protected:
    BoundingBox renderBounds;

    virtual bool coordinateInShape(Coordinate coordinate) = 0;

    virtual HSLColor calculateColor(Coordinate coordinate) = 0;

    static BoundingBox calculateBoundingBox(Coordinate origin, int width, int height);

public:
    Shape(Coordinate origin, HSLColor rootColor, BoundingBox renderBounds);

    void render(LedMatrixProxy &ledMatrix) override;

    virtual void grow() = 0;

    virtual void shrink() = 0;
};

}

#endif //PERFORMER_SHAPE_H
