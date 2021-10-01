#include "DisplaySignalMovement.h"

namespace performer {

DisplaySignalMovement::DisplaySignalMovement(LedMatrixProxy &ledMatrix,
                                             impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          hue{120},
          previousDisplaySignal{},
          lastColorChangeTimestamp{0},
          minimumTimeBetweenColorChanges{1000 * 100},
          energyRequiredForColorChangeMultiplier{1},
          sampleModifierAlpha{1},
          sampleModifierBeta{1} {

}

void DisplaySignalMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 11) {
            sampleModifierAlpha = morsel->value();
        } else if (morsel->field() == 12) {
            sampleModifierBeta = morsel->value() * 100;
        } else if (morsel->field() == 13) {
            energyRequiredForColorChangeMultiplier = morsel->value() * 2;
        }
    }
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::displaySignal) {
        auto displaySignal = calculateDisplaySignal(packet);
        if (previousDisplaySignal.empty()) {
            previousDisplaySignal.resize(displaySignal->size());
        }
        auto derivativeSignal = addDerivative(*displaySignal);
        hue = doctorHue(*displaySignal);

        // render the lights
        actionCollection.clear();
        auto action = std::make_unique<DisplaySignalAction>(
                ledMatrix, move(derivativeSignal), static_cast<uint32_t>(hue), sampleModifierAlpha, sampleModifierBeta
        );
        actionCollection.addAction(move(action));

        // record current signal
        for (int index = 0; index < displaySignal->size(); index++) {
            previousDisplaySignal[index] = (*displaySignal)[index];
        }
    }
}

std::unique_ptr<std::vector<float>> DisplaySignalMovement::calculateDisplaySignal(
        const impresarioUtils::Packet &packet) {
    auto rawDisplaySignal = packet.getDisplaySignal();
    auto samples = rawDisplaySignal->samples();
    auto displaySignal = std::make_unique<std::vector<float>>();
    displaySignal->reserve(samples->size());
    for (int index = 0; index < samples->size(); index++) {
        auto sample = samples->Get(index);
        if (sample < 0) {
            sample = 0;
        }

        // due to mel filterbank overflow, that last triangular filter catches everything above it
        // accommodate for crazy large last sample - this will go once those ridiculous triangular filters are changed
        if (index == samples->size() - 1) {
            sample /= 100;
        }

        // add sample
        displaySignal->push_back(sample);
    }
    return displaySignal;
}

std::unique_ptr<std::vector<float>> DisplaySignalMovement::addDerivative(const std::vector<float> &inputSignal) {
    auto result = std::make_unique<std::vector<float>>();
    result->reserve(inputSignal.size());
    for (int index = 0; index < inputSignal.size(); index++) {
        auto sample = inputSignal[index];
        auto previousSample = previousDisplaySignal[index];
        auto derivative = sample - previousSample;
        if (derivative > 0) {
            sample += derivative;
        }
        result->push_back(sample);
    }
    return result;
}

int DisplaySignalMovement::doctorHue(const std::vector<float> &displaySignal) {
    float currentEnergy = 0;
    for (int index = 0; index < displaySignal.size(); index++) {
        currentEnergy += displaySignal[index];
    }
    float previousEnergy = 0;
    for (int index = 0; index < previousDisplaySignal.size(); index++) {
        previousEnergy += previousDisplaySignal[index];
    }
    if (currentEnergy - previousEnergy > previousEnergy * energyRequiredForColorChangeMultiplier &&
        impresarioUtils::getElapsedTime(lastColorChangeTimestamp) > minimumTimeBetweenColorChanges) {
        lastColorChangeTimestamp = impresarioUtils::getCurrentTime();
        return LedGizmos::generateSignificantlyDifferentHue(randomNumberGenerator, hue, 50);
    }
    return hue;
}

void DisplaySignalMovement::handleTick() {

}

}
