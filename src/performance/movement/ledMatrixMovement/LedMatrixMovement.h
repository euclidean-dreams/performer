#ifndef PERFORMER_LEDMATRIXMOVEMENT_H
#define PERFORMER_LEDMATRIXMOVEMENT_H

#include <ImpresarioUtils.h>
#include "ledMatrix/LedMatrixProxy.h"
#include "performance/movement/Movement.h"
#include "performance/action/ActionCollection.h"

namespace performer {

class LedMatrixMovement : public Movement {
protected:
    LedMatrixProxy &ledMatrix;
    impresarioUtils::RandomNumberGenerator &randomNumberGenerator;
    ActionCollection actionCollection;
    int tick;

    virtual void handleTick() = 0;

public:
    LedMatrixMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void conduct() override;
};

}

#endif //PERFORMER_LEDMATRIXMOVEMENT_H
