#ifndef PERFORMER_LEDMATRIXACTION_H
#define PERFORMER_LEDMATRIXACTION_H

#include <ImpresarioUtils.h>
#include "ledMatrix/LedMatrixProxy.h"
#include "performance/action/Action.h"

namespace performer {

class LedMatrixAction : public Action {
protected:
    LedMatrixProxy &ledMatrix;
    uint64_t initialTimestamp;
    int tick;

    virtual void handleTick() = 0;

public:
    explicit LedMatrixAction(LedMatrixProxy &ledMatrix);

    ~LedMatrixAction() override = default;

    void execute() override;
};

}

#endif //PERFORMER_LEDMATRIXACTION_H
