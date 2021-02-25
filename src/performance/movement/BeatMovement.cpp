#include "BeatMovement.h"

BeatMovement::BeatMovement(LedMatrix &ledMatrix, RandomNumberGenerator &randomNumberGenerator)
        : ledMatrix{ledMatrix},
          randomNumberGenerator{randomNumberGenerator},
          actions{} {
}

void BeatMovement::present(uint32_t tick, const AudioAttributes *audioAttributes) {
//    if (audioAttributes != nullptr) {
//        auto onsetAggregate = audioAttributes->onsetAggregate();
//        for (int i = 0; i < onsetAggregate->methods()->size(); i++) {
//            auto timestamp = (*onsetAggregate->timestamps())[i];
//            auto onsetMethod = (*onsetAggregate->methods())[i];
//            uint32_t hue;
//            uint8_t saturation;
//            uint8_t lightness;
//            if (timestamp == 0) {
//                hue = 0;
//                saturation = 0;
//                lightness = 0;
//            } else if (getCurrentTime() - timestamp < 10000) {
//                hue = onsetMethod * 40;
//                saturation = 100;
//                lightness = 50;
//            } else {
//                hue = onsetMethod * 40;
//                saturation = 100;
//                lightness = 85;
//            }
//            auto color = HSLColor{hue, saturation, lightness};
////            auto beatSize = static_cast<int>(floor(ledMatrix.getLedCount() / (static_cast<double>(OnsetMethod::MAX) + 1)));
//            auto beatSize = 3;
//            auto startIndex = onsetMethod * beatSize;
//            auto endIndex = onsetMethod * beatSize + beatSize;
//            if (endIndex > ledMatrix.getLedCount()) {
//                endIndex = ledMatrix.getLedCount();
//            }
//            Beat beat{tick, ledMatrix, startIndex, endIndex, color};
//            beat.execute(tick);
//        }
//    } else {
//        auto color = HSLColor{0, 0, 0};
//        Beat beat{tick, ledMatrix, 0, 27, color};
//        beat.execute(tick);
//    }

    if (audioAttributes != nullptr) {
        auto onsetAggregate = audioAttributes->onsetAggregate();
        auto onsetsDetected = 0;
        for (int i = 0; i < onsetAggregate->methods()->size(); i++) {
            auto timestamp = (*onsetAggregate->timestamps())[i];
            if (timestamp > 0 && getCurrentTime() - timestamp < 10000) {
                onsetsDetected++;
            }
        }

        if (onsetsDetected > 0) {
            auto beatCount = randomNumberGenerator.generate(15) + 5;
            for (int i = 0; i < beatCount; i++) {
                auto hue = static_cast<uint32_t>(randomNumberGenerator.generate(361));
                auto color = HSLColor{hue, 100, 50};
                auto beatSize = static_cast<int>(floor(ledMatrix.getLedCount() / (beatCount)));
                auto startIndex = i * beatSize;
                auto endIndex = i * beatSize + beatSize;
                if (endIndex > ledMatrix.getLedCount()) {
                    endIndex = ledMatrix.getLedCount();
                }
                actions.emplace_back(make_unique<Beat>(tick, ledMatrix, startIndex, endIndex, color));
            }
        }
    }
    auto iterator = actions.begin();
    while (iterator != actions.end()) {
        (*iterator)->execute(tick);
        if ((*iterator)->finished()) {
            iterator = actions.erase(iterator);
        } else {
            iterator++;
        }
    }
}
