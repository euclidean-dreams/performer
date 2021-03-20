#ifndef PERFORMER_FLASHONONSETMOVEMENT_H
#define PERFORMER_FLASHONONSETMOVEMENT_H

#include <Time.h>
#include <Onset_generated.h>
#include "Config.h"
#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"
#include "performance/action/ledMatrixAction/Flash.h"

namespace performer {

class FlashOnOnsetMovement : public LedMatrixMovement {
private:
    inline static const int MIN_TIME_BETWEEN_ONSETS = 3000;

    std::unique_ptr<std::vector<ImpresarioSerialization::FrequencyBand>> frequencyBands;
    HSLColor color;
    int startIndex;
    int endIndex;
    float flashFadeRate;
    uint64_t lastAction;

public:
    static std::pair<std::unique_ptr<FlashOnOnsetMovement>, std::unique_ptr<FlashOnOnsetMovement>>
    createSymmetrical(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                      const TimelineManager &timelineManager,
                      std::vector<ImpresarioSerialization::FrequencyBand> frequencyBands, HSLColor color,
                      int startIndex, int endIndex, float flashFadeRate);

    FlashOnOnsetMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                         const TimelineManager &timelineManager,
                         std::unique_ptr<std::vector<ImpresarioSerialization::FrequencyBand>> frequencyBands,
                         HSLColor color, int startIndex, int endIndex, float flashFadeRate);

    void handleEvent(const Event &event) override;
};

}

#endif //PERFORMER_FLASHONONSETMOVEMENT_H
