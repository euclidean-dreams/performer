#include "FlashOnOnsetMovement.h"

namespace performer {

std::pair<std::unique_ptr<FlashOnOnsetMovement>, std::unique_ptr<FlashOnOnsetMovement>>
FlashOnOnsetMovement::createSymmetrical(LedMatrixProxy &ledMatrix,
                                        impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                        const TimelineManager &timelineManager,
                                        std::vector<ImpresarioSerialization::FrequencyBand> frequencyBands,
                                        HSLColor color, int startIndex, int endIndex, float flashFadeRate) {
    auto leftFrequencyBands = std::make_unique<std::vector<ImpresarioSerialization::FrequencyBand>>(frequencyBands);
    auto leftMovement = std::make_unique<FlashOnOnsetMovement>(ledMatrix, randomNumberGenerator, timelineManager,
                                                               move(leftFrequencyBands), color, startIndex, endIndex,
                                                               flashFadeRate);

    auto rightStartIndex = ledMatrix.size() - 1 - endIndex;
    auto rightEndIndex = ledMatrix.size() - 1 - startIndex;
    auto rightFrequencyBands = std::make_unique<std::vector<ImpresarioSerialization::FrequencyBand>>(frequencyBands);
    auto rightMovement = std::make_unique<FlashOnOnsetMovement>(ledMatrix, randomNumberGenerator, timelineManager,
                                                                move(rightFrequencyBands), color, rightStartIndex,
                                                                rightEndIndex, flashFadeRate);
    return {move(leftMovement), move(rightMovement)};
}

FlashOnOnsetMovement::FlashOnOnsetMovement(LedMatrixProxy &ledMatrix,
                                           impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                           const TimelineManager &timelineManager,
                                           std::unique_ptr<std::vector<ImpresarioSerialization::FrequencyBand>> frequencyBands,
                                           HSLColor color, int startIndex, int endIndex, float flashFadeRate)
        : LedMatrixMovement{ledMatrix, randomNumberGenerator, timelineManager},
          frequencyBands{move(frequencyBands)},
          color{color},
          startIndex{startIndex},
          endIndex{endIndex},
          lastAction{0},
          flashFadeRate{flashFadeRate} {

}

void FlashOnOnsetMovement::handleEvent(const Event &event) {
    if (event.getIdentifier() == ImpresarioSerialization::Identifier::onset) {
        auto onset = event.getOnset();
        auto onsetInCorrectFrequencyBand = false;
        for (auto frequencyBand : *frequencyBands) {
            if (onset->frequencyBand() == frequencyBand) {
                onsetInCorrectFrequencyBand = true;
            }
        }
        if (onsetInCorrectFrequencyBand && impresarioUtils::getElapsedTime(lastAction) > MIN_TIME_BETWEEN_ONSETS
            && onsetLatencyReasonable(onset)) {
            lastAction = impresarioUtils::getCurrentTime();
            auto flash = std::make_unique<Flash>(ledMatrix, color, startIndex, endIndex, flashFadeRate);
            actionCollection.addAction(move(flash));
        }
    }
}

}
