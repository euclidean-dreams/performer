#ifndef PERFORMER_LINDOGRAM_H
#define PERFORMER_LINDOGRAM_H

#include <ledMatrix/Coordinate.h>
#include "performance/action/ledMatrixAction/entity/Entity.h"

namespace performer {

class Lindogram : public Entity {
protected:
    impresarioUtils::Point location;
    double initialOrientation;
    double orientation;
    std::vector<char> state;
    int currentTimeling;

    virtual void applyRules(std::vector<char> &newState, char symbol) = 0;

    virtual void processSymbol(char symbol) = 0;

    void advance(double distance);

    void rotate(double radians);

public:
    Lindogram(Coordinate origin, HSLColor rootColor, double orientation);

    void render(LedMatrixProxy &ledMatrix) override;

    void recurse();

    void tick();
};

}

#endif //PERFORMER_LINDOGRAM_H
