#ifndef PERFORMER_FLAMEACTION_H
#define PERFORMER_FLAMEACTION_H

#include "performance/action/ledMatrixAction/entity/shape/Flame.h"
#include "ledMatrix/Coordinate.h"
#include "performance/action/ledMatrixAction/LedMatrixAction.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class FlameAction : public LedMatrixAction {
private:
    impresarioUtils::RandomNumberGenerator &randomNumberGenerator;
    std::vector<std::unique_ptr<Flame>> flameStack;
    float currentLightness;
    bool ramping;
    int mode;

public:
    FlameAction(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                Coordinate origin, HSLColor color, int width, int height, int mode);

    bool finished() override;

    void handleTick() override;

    void flicker(float intensity);
};

}

#endif //PERFORMER_FLAMEACTION_H
