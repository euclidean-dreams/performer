#include "DisplaySignalMovement.h"

namespace performer {

DisplaySignalMovement::DisplaySignalMovement(LedMatrixProxy &ledMatrix,
                                             impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                             const TimelineManager &timelineManager)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator, timelineManager),
          logMovingAverageValues{},
          logMovingAverageValues2{},
          powerMovingAverageValues{},
          powerTransparencyThreshold{4},
          lastDisplaySignal{},
          lastHue{280} {
    lastDisplaySignal.reserve(180);
}

void DisplaySignalMovement::handleEvent(const Event &event) {
    if (event.getIdentifier() == ImpresarioSerialization::Identifier::displaySignal) {
        // obligatory signal stuff
        auto displaySignal = event.getDisplaySignal();
        auto samples = displaySignal->samples();
        auto history = 10;
        if (lastDisplaySignal.empty()) {
            for (int index = 0; index < samples->size(); index++) {
                lastDisplaySignal.push_back(samples->Get(index));
            }
        }

        // let's get some features
        for (int iteration = 0; iteration < 1; iteration++) {
            float currentLogMax = 0;
            float currentLogMean = 0;
            float currentLogMaxIndex = 0;
            auto logSamples = std::make_unique<std::vector<float>>();
            int sumMagnitude = 0;
            logSamples->reserve(ledMatrix.size());
            for (int index = 0; index < ledMatrix.size(); index++) {
                // formatting
                auto sample = samples->Get(index);
                if (sample < 0) {
                    sample = 0;
                }

                // lego
                float logSample;
                if (iteration == 0) {
                    logSample = std::pow(sample, 1);//static_cast<float>(std::pow(std::log(sample + 1), 1));
                } else {
                    auto specFlux = sample - lastDisplaySignal[index];
                    if (specFlux < 0) {
                        specFlux = 0;
                    }
                    logSample = sample;//static_cast<float>(std::pow(sample, 1));// + specFlux * 20);
                    lastDisplaySignal[index] = sample;
                }
                if (logSample < 0) {
                    logSample = 0;
                }
                currentLogMean += logSample;
                if (logSample > currentLogMax) {
                    currentLogMax = logSample;
                    currentLogMaxIndex = index;
                }
                sumMagnitude += logSample;
                logSamples->push_back(logSample);
//                lastDisplaySignal.push_back(sample);
            }
            currentLogMean = currentLogMean / ledMatrix.size();
            while (logSumValues.size() > history) {
                logSumValues.pop_front();
            }
            logSumValues.push_back(sumMagnitude);

            float logSumMean;
            for (auto sumMagnitude: logSumValues) {
                logSumMean += sumMagnitude;
            }
            logSumMean = logSumMean / logSumValues.size();

            float sumVariance;
            for (auto sumMagnitude: logSumValues) {
                sumVariance += std::pow(sumMagnitude - logSumMean, 2);
            }
            auto logSumStandardDeviation = std::sqrt(1 / logSumValues.size() * sumVariance);

            ////
            //// Thus begins the Loggery
            ////

            // moving average chicanery
            auto logMovingAverage = 0.0;
            if (iteration == 0) {
                if (logMovingAverageValues.size() > history) {
                    logMovingAverageValues.pop_front();
                }
                logMovingAverageValues.push_back(currentLogMean);
                for (auto value: logMovingAverageValues) {
                    logMovingAverage += value;
                }
                logMovingAverage = logMovingAverage / logMovingAverageValues.size();
                if (logMovingAverage < currentLogMax) {
                    logMovingAverage = currentLogMax;
                }
            } else {
                if (logMovingAverageValues2.size() > history) {
                    logMovingAverageValues2.pop_front();
                }
                logMovingAverageValues2.push_back(currentLogMean);
                for (auto value: logMovingAverageValues2) {
                    logMovingAverage += value;
                }
                logMovingAverage = logMovingAverage / logMovingAverageValues2.size();
                if (logMovingAverage < currentLogMax) {
                    logMovingAverage = currentLogMax;
                }
            }

            //        auto action = std::make_unique<DisplaySignalAction>(ledMatrix, move(logSamples), 0.001, logMovingAverage,
            //                                                            bassMovingAverage);
            //        actionCollection.addAction(move(action));
            //        actionCollection.trimActions(1);

            // logarithmic wonderland
            for (int index = 0; index < ledMatrix.size(); index++) {
                auto sample = (*logSamples)[index];
                int baseHue = lastHue;
//                if (randomNumberGenerator.generate(10000) > 9990) {
//                    baseHue += 1;
//                }
                if (baseHue > 320) {
                    baseHue = baseHue - 360;
                }
                if (baseHue < 0) {
                    baseHue = 360 + baseHue;
                }
                lastHue = baseHue;
                uint32_t hue;
                uint8_t saturation;
                uint8_t lightness;
                if (iteration == 0) {
                    hue = baseHue - 280 * sample / logMovingAverage;
                    saturation = 100;
                    lightness = 50 * sample / logMovingAverage; //+ 40 * sample / movingAverage;
                } else {
                    hue = baseHue - 280 * sample / logMovingAverage;
                    saturation = 50 + 50 * sample / logMovingAverage;
                    lightness = 50 * sample / logMovingAverage; //+ 40 * sample / movingAverage;
                }
                if (hue > 360) {
                    hue = hue - 360;
                }
                if (hue < 0) {
                    hue = 360 + hue;
                }
                if (iteration == 0) {
                    ledMatrix[index] = HSLColor{hue, saturation, lightness};
                } else if (iteration == 1 && lightness > 5) {
                    ledMatrix[index] = HSLColor{hue, saturation, lightness};
                }
            }

//            if (iteration == 1 && currentLogMax >= logMovingAverage) {
//                auto blockSize = 2;
//                for (int i = 0; i < blockSize; i++) {
//                    uint32_t hue;
//                    uint8_t saturation;
//                    uint8_t lightness;
//                    hue = 190;
//                    saturation = 40 + 20 * (blockSize - i) / blockSize;
//                    lightness = 50 + 20 * (blockSize - i) / blockSize;
//                    auto testIndex = currentLogMaxIndex + i;
//                    if (testIndex < ledMatrix.size()) {
//                        ledMatrix[testIndex] = HSLColor{hue, saturation, lightness};
//                    } else {
//                        ledMatrix[ledMatrix.size() - 1] = HSLColor{hue, saturation, lightness};
//                    }
//                    testIndex = currentLogMaxIndex - i;
//                    if (testIndex > 0) {
//                        ledMatrix[testIndex] = HSLColor{hue, saturation, lightness};
//                    } else {
//                        ledMatrix[0] = HSLColor{hue, saturation, lightness};
//                    }
//                }
//            }
        }

        ////
        //// And onward to the land of fresh pow
        ////

//        // grab some attributes
//        powerMean = powerMean / static_cast<float>(powerSamples.size());
//
//        auto sumVariance = 0.0;
//        for (float powerSample : powerSamples) {
//            sumVariance += std::pow(powerSample - powerMean, 2);
//        }
//        auto powerStandardDeviation = std::sqrt(sumVariance / powerSamples.size());
//
//        // moving average chicanery
//        if (powerMovingAverageValues.size() > 100) {
//            powerMovingAverageValues.pop_front();
//        }
//        powerMovingAverageValues.push_back(currentLogMax);
//
//        auto powerMovingAverage = 0.0;
//        for (auto value: powerMovingAverageValues) {
//            powerMovingAverage += value;
//        }
//        powerMovingAverage = powerMovingAverage / powerMovingAverageValues.size();
//        if (powerMovingAverage < currentPowMax) {
//            powerMovingAverage = currentPowMax;
//        }
//
//        // delicious pow
//        for (int index = bassCutoff; index < ledMatrix.size(); index++) {
//            auto sample = powerSamples[index];
//            if (sample > powerMean + powerTransparencyThreshold * powerStandardDeviation) {
//                uint32_t hue = 0;
//                uint8_t saturation = 100;
//                uint8_t lightness = 50 + 20 * sample / powerMovingAverage;
//                if (index > 0) {
//                    // add lower component
//                    ledMatrix[index - 1] = HSLColor{hue, saturation, lightness};
//                }
//                if (index < ledMatrix.size()) {
//                    // add upper component
//                    ledMatrix[index + 1] = HSLColor{hue, saturation, lightness};
//                }
//                ledMatrix[index] = HSLColor{hue, saturation, lightness};
//            }
//        }

        ////
        //// A graveyard for ideas
        ////

//        // old idea - also good idea
//        std::vector<float> powerSamples{};
//        powerSamples.reserve(allPowerSamples.size() - bassCutoff);
//        std::vector<float> bassPowerSamples{};
//        bassPowerSamples.reserve(bassCutoff);
//        for (int index = 0; index < allPowerSamples.size(); ++index) {
//            if (index < bassCutoff) {
//                bassPowerSamples.push_back(allPowerSamples[index]);
//            } else {
//                powerSamples.push_back(allPowerSamples[index]);
//            }
//        }
//        std::sort(begin(powerSamples), end(powerSamples));
//        std::sort(begin(bassPowerSamples), end(bassPowerSamples));
//        auto peakCount = 10;
//        auto highestSampleToConsider = powerSamples[powerSamples.size() - peakCount];
//        auto bassPeakCount = 10;
//        auto bassHighestSampleToConsider = bassPowerSamples[bassPowerSamples.size() - bassPeakCount];
//        std::vector<bool> shouldLight;
//        std::vector<bool> bassShouldLight;
//        shouldLight.resize(ledMatrix.size());
//        bassShouldLight.resize(ledMatrix.size());
//        for (int index = 0; index < ledMatrix.size(); index++) {
//            auto sample = allPowerSamples[index];
//            if (sample > highestSampleToConsider) {
//                if (index < bassCutoff) {
//                    bassShouldLight[index] = true;
//                } else {
//                    shouldLight[index] = true;
//                }
//            }
//        }
//
//        std::vector<int> peakIndicies {};
//
//
//
//
//
//        for (int index = 0; index < ledMatrix.size(); index++) {
//            if (shouldLight[index] || bassShouldLight[index]) {
//                uint32_t hue;
//                uint8_t saturation;
//                uint8_t lightness;
//                hue = 20;
//                saturation = 100;
//                lightness = 50;
//                ledMatrix[index] = HSLColor{hue, saturation, lightness};
//            }
//        }
//
//        for (int index = 0; index < ledMatrix.size(); index++) {
//            if (shouldLight[index]) {
//                uint32_t hue;
//                uint8_t saturation;
//                uint8_t lightness;
//                hue = 0;
//                saturation = 100;
//                lightness = 50;
//                ledMatrix[index] = HSLColor{hue, saturation, lightness};
//            } else if (bassShouldLight[index]) {
//                uint32_t hue;
//                uint8_t saturation;
//                uint8_t lightness;
//                hue = 20;
//                saturation = 100;
//                lightness = 50;
//                ledMatrix[index] = HSLColor{hue, saturation, lightness};
//            }
//        }

    }
}

}
