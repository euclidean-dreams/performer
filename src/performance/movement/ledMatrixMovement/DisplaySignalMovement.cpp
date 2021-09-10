#include "DisplaySignalMovement.h"

namespace performer {

DisplaySignalMovement::DisplaySignalMovement(LedMatrixProxy &ledMatrix,
                                             impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                             const TimelineManager &timelineManager,
                                             std::unique_ptr<impresarioUtils::NetworkSocket> morselSocket)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator, timelineManager),
          morselSocket{move(morselSocket)},
          previousDisplaySignal{},
          baseHue{280},
          baseLightnessMultiplier{50},
          lightnessMultiplier{baseLightnessMultiplier},
          floatingParameter{0},
          lastColorChangeTimestamp{0},
          minimumTimeBetweenColorChanges{1000 * 100},
          mode{0},
          highestSampleIndex{0},
          lastActionTimestamp{0} {
    previousDisplaySignal.resize(Bootstrapper::LED_COUNT, 0);
}

void DisplaySignalMovement::handleEvent(const Event &event) {
    auto morselWrapper = morselSocket->receiveSerializedData(zmq::recv_flags::dontwait);
    if (morselWrapper != nullptr) {
        if (morselWrapper->getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
            auto morsel = ImpresarioSerialization::GetFloatMorsel(morselWrapper->getBuffer());
            if (morsel->field() == 10) {
                floatingParameter = morsel->value();
            } else if (morsel->field() == 11) {
                lightnessMultiplier = morsel->value() * baseLightnessMultiplier;
            } else if (morsel->field() == 100) {
                baseHue = getNewHue(baseHue);
            } else if (morsel->field() == 101) {
                auto color = HSLColor{getNewHue(baseHue), 100, 50};
                auto index = randomNumberGenerator.generate(ledMatrix.size());
                auto ripple = std::make_unique<Ripple>(ledMatrix, color, index, 1);
                actionCollection.addAction(move(ripple));
            } else if (morsel->field() == 102) {
                auto color = HSLColor{getNewHue(baseHue), 100, 50};
                auto flash = std::make_unique<Flash>(ledMatrix, color, 0, ledMatrix.size() - 1, 0.15);
                actionCollection.addAction(move(flash));
            } else if (morsel->field() == 103) {
                mode = 0;
            } else if (morsel->field() == 104) {
                mode = 1;
            } else if (morsel->field() == 105) {
                mode = 2;
            }
        }
    }
    if (event.getIdentifier() == ImpresarioSerialization::Identifier::displaySignal) {
        // obligatory signal stuff
        auto rawDisplaySignal = event.getDisplaySignal();
        auto samples = rawDisplaySignal->samples();

        // let's prepare the signal for display
        float highestSample = 0;
        auto displaySignal = std::vector<float>{};
        displaySignal.reserve(ledMatrix.size());
        for (int index = 0; index < ledMatrix.size(); index++) {
            auto sample = samples->Get(index);
            // accommodate for crazy large last sample - this will go once those ridiculous triangular filters are changed
            if (index == ledMatrix.size() - 1) {
                sample /= 100;
            }

            if (sample < 0) {
                sample = 0;
            }

            if (sample > highestSample) {
                highestSample = sample;
                highestSampleIndex = index;
            }

            displaySignal.push_back(sample);
        }

        // collect total energy
        float currentEnergy = 0;
        float previousEnergy = 0;
        for (int index = 0; index < ledMatrix.size(); index++) {
            currentEnergy += displaySignal[index];
            previousEnergy += previousDisplaySignal[index];
        }

        for (int index = 0; index < ledMatrix.size(); index++) {
            // add derivative
            auto sample = displaySignal[index];
            auto previousSample = previousDisplaySignal[index];
            auto derivative = sample - previousSample;
            if (derivative > 0) {
                sample += derivative;
            }

            // high energy activity
            if (currentEnergy - previousEnergy > previousEnergy * (floatingParameter * 2) &&
                impresarioUtils::getElapsedTime(lastColorChangeTimestamp) > minimumTimeBetweenColorChanges) {
                lastColorChangeTimestamp = impresarioUtils::getCurrentTime();
                baseHue = getNewHue(baseHue);
            }

            // assign lights
            uint32_t hue;
            uint8_t saturation;
            uint8_t lightness;
            saturation = 100;
            hue = baseHue;
            float rawLightness = sample * lightnessMultiplier;
            if (rawLightness > 100) {
                rawLightness = 100;
            }
            lightness = static_cast<uint8_t>(rawLightness);
            if (mode == 0) {
                ledMatrix[index] = HSLColor{hue, saturation, lightness};
            }
        }
        for (int index = 0; index < displaySignal.size(); index++) {
            previousDisplaySignal[index] = displaySignal[index];
        }

        if (mode == 1) {
            if (impresarioUtils::getElapsedTime(lastActionTimestamp) >
                (10 - 9 * static_cast<uint64_t>(floatingParameter)) * 1000 * 100) {
                lastActionTimestamp = impresarioUtils::getCurrentTime();
                auto color = HSLColor{getNewHue(baseHue), 100, 50};
                auto index = randomNumberGenerator.generate(ledMatrix.size());
                auto ripple = std::make_unique<Ripple>(ledMatrix, color, index, 0.5 + floatingParameter);
                actionCollection.addAction(move(ripple));
            }
        } else if (mode == 2) {
            if (impresarioUtils::getElapsedTime(lastActionTimestamp) >
                (5 - 4 * static_cast<uint64_t>(floatingParameter)) * 1000 * 100) {
                lastActionTimestamp = impresarioUtils::getCurrentTime();
                auto color = HSLColor{getNewHue(baseHue), 100, 50};
                int startIndex;
                int endIndex;
                while (startIndex >= endIndex) {
                    startIndex = randomNumberGenerator.generate(ledMatrix.size());
                    endIndex = randomNumberGenerator.generate(ledMatrix.size());
                }
                auto flash = std::make_unique<Flash>(ledMatrix, color, startIndex, endIndex, 0.15);
                actionCollection.addAction(move(flash));
            }
        }
    }
}

uint32_t DisplaySignalMovement::getNewHue(uint32_t initialHue) {
    int additive = 0;
    while (additive < 50) {
        additive = randomNumberGenerator.generate(HSL_HUE_MAX);
    }
    auto resultHue = initialHue + additive;
    while (resultHue > HSL_HUE_MAX) {
        resultHue -= HSL_HUE_MAX;
    }
    while (resultHue < 0) {
        resultHue += HSL_HUE_MAX;
    }
    return resultHue;
}

}
