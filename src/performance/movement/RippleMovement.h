#ifndef PERFORMER_RIPPLEMOVEMENT_H
#define PERFORMER_RIPPLEMOVEMENT_H

#include <list>
#include "action/Action.h"
#include "action/Ripple.h"
#include "RandomNumberGenerator.h"
#include "color/HSLColor.h"
#include "ledMatrix/LedMatrixProxy.h"
#include "Movement.h"
#include "eventReceiver/event/OnsetEvent.h"

class RippleMovement : public Movement {
private:
    LedMatrixProxy &ledMatrix;
    RandomNumberGenerator &randomNumberGenerator;
    list<std::unique_ptr<Action>> actions;
    Color::HSLColor lastColor;
    int mode;

    void createRipple(const OnsetEvent &event);

    Color::HSLColor generateRippleColor();

public:
    RippleMovement(LedMatrixProxy &ledMatrix, RandomNumberGenerator &randomNumberGenerator);

    void handleEvent(const Event &event) override;

    void conduct() override;
};

#endif //PERFORMER_RIPPLEMOVEMENT_H
