#ifndef PERFORMER_ENTITY_H
#define PERFORMER_ENTITY_H

#include <ImpresarioUtils.h>
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class Entity : impresarioUtils::NonCopyable {
protected:
    Coordinate origin;
    HSLColor rootColor;

public:
    Entity(Coordinate origin, HSLColor rootColor);

    virtual void render(LedMatrixProxy &ledMatrix) = 0;

    void setRootColor(HSLColor color);
};

}

#endif //PERFORMER_ENTITY_H
