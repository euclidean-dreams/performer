#ifndef PERFORMER_RIPPLEMOVEMENT_H
#define PERFORMER_RIPPLEMOVEMENT_H

#include <memory>
#include <list>
#include <RandomNumberGenerator.h>
#include "eventReceiver/event/OnsetEvent.h"
#include "ledMatrix/LedMatrixProxy.h"
#include "performance/movement/Movement.h"
#include "performance/movement/action/Ripple.h"

namespace performer {

class RippleMovement : public Movement {
private:
    LedMatrixProxy &ledMatrix;
    impresarioUtils::RandomNumberGenerator &randomNumberGenerator;
    std::list<std::unique_ptr<Action>> actions;
    HSLColor lastColor;
    int mode;
    uint64_t lastRipple;
    int minTimeBetweenRipples;

    void createRipple(const OnsetEvent &event);

    HSLColor generateRippleColor();

public:
    RippleMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator);

    void handleEvent(const Event &event) override;

    void conduct() override;
};

}

#endif //PERFORMER_RIPPLEMOVEMENT_H
