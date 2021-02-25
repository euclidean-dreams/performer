#ifndef PERFORMER_RIPPLEMOVEMENT_H
#define PERFORMER_RIPPLEMOVEMENT_H

#include <vector>
#include <list>
#include <memory>
#include "Utils.h"
#include "RandomNumberGenerator.h"
#include "AudioAttributes_generated.h"
#include "ledMatrix/LedMatrix.h"
#include "Movement.h"
#include "performance/movement/action/Ripple.h"

using namespace std;

class RippleMovement : public Movement {
private:
    LedMatrix &ledMatrix;
    RandomNumberGenerator &randomNumberGenerator;
    list<std::unique_ptr<Action>> actions;
    HSLColor lastColor;
    int mode;
    int lastIndex;

public:
    RippleMovement(LedMatrix &ledMatrix, RandomNumberGenerator &randomNumberGenerator);

    void present(uint32_t tick, const AudioAttributes *audioAttributes) override;
};

#endif //PERFORMER_RIPPLEMOVEMENT_H
