#include "performance/movement/ledMatrixMovement/LedMatrixMovement.h"

namespace performer {

LedMatrixMovement::LedMatrixMovement(LedMatrixProxy &ledMatrix,
                                     impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                     const TimelineManager &timelineManager)
        : ledMatrix{ledMatrix},
          randomNumberGenerator{randomNumberGenerator},
          timelineManager{timelineManager},
          actionCollection{} {

}

void LedMatrixMovement::conduct() {
    actionCollection.executeActions();
}

HSLColor LedMatrixMovement::generateColorWithDifferentHue(const HSLColor &baseColor) const {
    auto hue = static_cast<uint32_t>(randomNumberGenerator.generate(HSL_HUE_MAX));
    while (std::abs(static_cast<int>(hue - baseColor.getHue())) < 60) {
        hue = static_cast<uint32_t>(randomNumberGenerator.generate(HSL_HUE_MAX));
    }
    return HSLColor{hue, baseColor.getSaturation(), baseColor.getLightness()};
}

bool LedMatrixMovement::onsetLatencyReasonable(const ImpresarioSerialization::Onset * onset) {
    return impresarioUtils::getElapsedTime(onset->timestamp()) < MAX_ONSET_LATENCY;
}

}
