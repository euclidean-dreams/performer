#ifndef PERFORMER_FLASH_H
#define PERFORMER_FLASH_H

#include "performance/action/ledMatrixAction/LedMatrixAction.h"

namespace performer {

class Flash : public LedMatrixAction {
private:
    HSLColor color;
    int startIndex;
    int endIndex;
    float fadeRate;
    bool shouldContinue;

public:
    Flash(LedMatrixProxy &ledMatrix, HSLColor color, int startIndex, int endIndex, float fadeRate);

    void execute() override;

    bool finished() override;

    void cleanup() override;
};

}

#endif //PERFORMER_FLASH_H
