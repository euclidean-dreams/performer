#ifndef PERFORMER_PITCHTRACKINGMOVEMENT_H
#define PERFORMER_PITCHTRACKINGMOVEMENT_H

#include <memory>
#include <list>
#include <Time.h>
#include "Config.h"
#include "ledMatrix/LedMatrixProxy.h"
#include "performance/timeline/TimelineManager.h"
#include "performance/movement/Movement.h"

namespace performer {

class PitchTrackingMovement : public Movement {
private:
    inline static const int PITCH_SPREAD_MULTIPLIER = 3;
    inline static const int PITCH_MOVING_AVERAGE_SIZE = 500;

    LedMatrixProxy &ledMatrix;
    const TimelineManager &timelineManager;
    HSLColor lastColor;
    uint64_t lastColorChangeTimestamp;

public:
    PitchTrackingMovement(LedMatrixProxy &ledMatrix, const TimelineManager &timelineManager);

    void handleEvent(const Event &event) override;

    void conduct() override;
};

}

#endif //PERFORMER_PITCHTRACKINGMOVEMENT_H
