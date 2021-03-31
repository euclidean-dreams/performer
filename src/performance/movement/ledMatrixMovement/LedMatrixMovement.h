#ifndef PERFORMER_LEDMATRIXMOVEMENT_H
#define PERFORMER_LEDMATRIXMOVEMENT_H

#include <ImpresarioUtils.h>
#include "ledMatrix/LedMatrixProxy.h"
#include "performance/movement/Movement.h"
#include "performance/action/ActionCollection.h"
#include "performance/timeline/TimelineManager.h"

namespace performer {

class LedMatrixMovement : public Movement {
protected:
    LedMatrixProxy &ledMatrix;
    impresarioUtils::RandomNumberGenerator &randomNumberGenerator;
    const TimelineManager &timelineManager;
    ActionCollection actionCollection;

    HSLColor generateColorWithDifferentHue(const HSLColor &baseColor) const;

    static bool onsetLatencyReasonable(const ImpresarioSerialization::Onset *onset);

public:
    LedMatrixMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                      const TimelineManager &timelineManager);

    void conduct() override;
};

}

#endif //PERFORMER_LEDMATRIXMOVEMENT_H
