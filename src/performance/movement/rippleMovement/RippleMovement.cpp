#include "RippleMovement.h"

namespace performer {

RippleMovement::RippleMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                               const TimelineManager &timelineManager)
        : ledMatrix{ledMatrix},
          randomNumberGenerator{randomNumberGenerator},
          timelineManager{timelineManager},
          actions{},
          mode{randomNumberGenerator.generate(MODE_COUNT)},
          lastColor{0, 0, 0},
          lastRipple{0} {

}

void RippleMovement::handleEvent(const Event &event) {
    if (event.getIdentifier() == ImpresarioSerialization::Identifier::onset) {
        auto onset = event.getOnset();
        if (impresarioUtils::getElapsedTime(lastRipple) > MIN_TIME_BETWEEN_RIPPLES
            && impresarioUtils::getElapsedTime(onset->timestamp()) < MAX_ONSET_LATENCY) {
            createRipple(onset);
            lastRipple = impresarioUtils::getCurrentTime();
        }
    }
}

void RippleMovement::createRipple(const ImpresarioSerialization::Onset *onset) {
//    auto hueIncrement = HSL_HUE_MAX / static_cast<int>(ImpresarioSerialization::OnsetMethod::MAX);
//    HSLColor color{static_cast<unsigned int>(onset->method()) * hueIncrement, 100, 50};
    std::unique_ptr<Action> ripple;
    auto index = MIDI_MAX / 2;
    auto sum = 0;
    auto summedValueCount = 0;
    auto pitchIterator = timelineManager.getPitchTimeline().begin();
    auto endIterator = timelineManager.getPitchTimeline().end();
    if (pitchIterator != endIterator) {
        auto currentPitch = *pitchIterator;
        while (pitchIterator != endIterator && currentPitch->sampleTimestamp() > onset->timestamp()) {
            pitchIterator++;
            currentPitch = *pitchIterator;
        }
        while (pitchIterator != endIterator && summedValueCount < PITCH_MOVING_AVERAGE_SIZE) {
            sum += (*pitchIterator)->pitch();
            summedValueCount++;
            pitchIterator++;
        }
        auto averagePitch = sum / summedValueCount;
        auto pitchDifference = static_cast<float>(currentPitch->pitch() - averagePitch);
        auto pitchMultiplier = pitchDifference / 128 * PITCH_SPREAD_MULTIPLIER + 0.5;
        if (pitchMultiplier > 1) {
            pitchMultiplier = 1;
        }
        index = static_cast<float>(ledMatrix.size()) * pitchMultiplier;
    }
    HSLColor color{180, 100, 90};
    if (index < ledMatrix.size() / 3) {
        color = {0, 100, 50};
    } else if (index < ledMatrix.size() / 3 * 2) {
        color = generateRippleColor();
        lastColor = color;
    }
    ripple = std::make_unique<Ripple>(ledMatrix, index, color, 0.5);
    actions.push_back(move(ripple));
}

HSLColor RippleMovement::generateRippleColor() {
    auto hue = static_cast<uint32_t>(randomNumberGenerator.generate(361));
    while (std::abs(static_cast<int>(hue - lastColor.getHue())) < 60) {
        hue = static_cast<uint32_t>(randomNumberGenerator.generate(361));
    }
    auto color = HSLColor{hue, 100, 50};
    return color;
}

void RippleMovement::conduct() {
    auto iterator = actions.begin();
    while (iterator != actions.end()) {
        (*iterator)->execute();
        if ((*iterator)->finished()) {
            iterator = actions.erase(iterator);
        } else {
            iterator++;
        }
    }
}

}
