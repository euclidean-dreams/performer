#include "PitchTrackingMovement.h"

namespace performer {

PitchTrackingMovement::PitchTrackingMovement(LedMatrixProxy &ledMatrix, const TimelineManager &timelineManager)
        : ledMatrix{ledMatrix},
          timelineManager{timelineManager},
          lastColor{0, 100, 50},
          lastColorChangeTimestamp{0} {

}

void PitchTrackingMovement::handleEvent(const Event &event) {

}

void PitchTrackingMovement::conduct() {
    auto hue = lastColor.getHue();
    if (impresarioUtils::getElapsedTime(lastColorChangeTimestamp) > 5000) {
        hue++;
        if (hue > HSL_HUE_MAX) {
            hue = 0;
        }
        lastColorChangeTimestamp = impresarioUtils::getCurrentTime();
    }
    HSLColor color{hue, lastColor.getSaturation(), lastColor.getLightness()};
    lastColor = color;
    auto index = MIDI_MAX / 2;
    auto sum = 0;
    auto summedValueCount = 0;
    auto pitchIterator = timelineManager.getPitchTimeline().begin();
    auto endIterator = timelineManager.getPitchTimeline().end();
    if (pitchIterator != endIterator) {
        auto currentPitch = *pitchIterator;
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
    for (int i = 0; i < ledMatrix.size(); i++) {
        ledMatrix[i] = {0, 0, 0};
    }
    ledMatrix[index] = color;
}

}
