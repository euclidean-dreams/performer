#ifndef PERFORMER_BEATMOVEMENT_H
#define PERFORMER_BEATMOVEMENT_H

#include <list>
#include "Utils.h"
#include "RandomNumberGenerator.h"
#include "AudioAttributes_generated.h"
#include "ledMatrix/LedMatrix.h"
#include "Movement.h"
#include "color/HSLColor.h"
#include "performance/movement/action/Beat.h"

class BeatMovement : public Movement {
private:
    LedMatrix &ledMatrix;
    RandomNumberGenerator &randomNumberGenerator;
    list<std::unique_ptr<Action>> actions;

public:
    explicit BeatMovement(LedMatrix &ledMatrix, RandomNumberGenerator &randomNumberGenerator);

    void present(uint32_t tick, const AudioAttributes *audioAttributes) override;
};

#endif //PERFORMER_BEATMOVEMENT_H
