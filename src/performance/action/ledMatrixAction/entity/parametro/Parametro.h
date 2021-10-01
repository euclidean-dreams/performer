#ifndef PERFORMER_PARAMETRO_H
#define PERFORMER_PARAMETRO_H

#include <ledMatrix/Coordinate.h>
#include "performance/action/ledMatrixAction/entity/Entity.h"

namespace performer {

class Parametro : public Entity {
protected:
    int currentTimeling;

    virtual Coordinate calculateCoordinate(int timeling) = 0;

    virtual HSLColor calculateColor(Coordinate coordinate) = 0;

public:
    Parametro(Coordinate origin, HSLColor rootColor);

    void render(LedMatrixProxy &ledMatrix) override;

    void advance();
};

}

#endif //PERFORMER_PARAMETRO_H
