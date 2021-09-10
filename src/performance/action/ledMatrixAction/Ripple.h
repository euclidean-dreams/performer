#ifndef PERFORMER_RIPPLE_H
#define PERFORMER_RIPPLE_H

#include "performance/action/ledMatrixAction/LedMatrixAction.h"

namespace performer {

class Ripple : public LedMatrixAction {
private:
    HSLColor color;
    int startIndex;
    float speed;
    bool shouldContinue;

public:
    Ripple(performer::LedMatrixProxy &ledMatrix, performer::HSLColor color, int startIndex, float speed);

    void execute() override;

    bool finished() override;

    void cleanup() override;
};

}

#endif //PERFORMER_RIPPLE_H
