#ifndef PERFORMER_RIPPLEMOVEMENT_H
#define PERFORMER_RIPPLEMOVEMENT_H

#include <memory>
#include <list>
#include <RandomNumberGenerator.h>
#include <Onset_generated.h>
#include <Pitch_generated.h>
#include "Config.h"
#include "ledMatrix/LedMatrixProxy.h"
#include "performance/timeline/TimelineManager.h"
#include "performance/movement/Movement.h"
#include "performance/movement/action/Ripple.h"

namespace performer {

class RippleMovement : public Movement {
private:
    inline static const int MODE_COUNT = 2;
    inline static const int MIN_TIME_BETWEEN_RIPPLES = 3000;
    inline static const int PITCH_SPREAD_MULTIPLIER = 3;
    inline static const int PITCH_MOVING_AVERAGE_SIZE = 500;
    inline static const int MAX_ONSET_LATENCY = 10000;

    LedMatrixProxy &ledMatrix;
    impresarioUtils::RandomNumberGenerator &randomNumberGenerator;
    const TimelineManager &timelineManager;
    std::list<std::unique_ptr<Action>> actions;
    int mode;
    HSLColor lastColor;
    uint64_t lastRipple;

    void createRipple(const ImpresarioSerialization::Onset *onset);

    HSLColor generateRippleColor();

public:
    RippleMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                   const TimelineManager &timelineManager);

    void handleEvent(const Event &event) override;

    void conduct() override;
};

}

#endif //PERFORMER_RIPPLEMOVEMENT_H
