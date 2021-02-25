#ifndef PERFORMER_BEAT_H
#define PERFORMER_BEAT_H

#include "ledMatrix/LedMatrix.h"
#include "color/HSLColor.h"
#include "Action.h"

class Beat : public Action {
private:
    LedMatrix &ledMatrix;
    int startIndex;
    int endIndex;
    HSLColor color;
    bool shouldContinue;

public:
    explicit Beat(uint32_t initialTick, LedMatrix &ledMatrix, int startIndex, int endIndex, HSLColor color);

    void execute(uint32_t tick) override;

    bool finished() override;
};

#endif //PERFORMER_BEAT_H
