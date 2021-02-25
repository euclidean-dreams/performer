#include <performance/movement/action/Beat.h>
#include "RippleMovement.h"

RippleMovement::RippleMovement(LedMatrix &ledMatrix, RandomNumberGenerator &randomNumberGenerator)
        : ledMatrix{ledMatrix},
          randomNumberGenerator{randomNumberGenerator},
          actions{},
          lastColor{0, 0, 0},
          mode{static_cast<bool>(randomNumberGenerator.generate(4))},
          lastIndex{0} {
}

void RippleMovement::present(uint32_t tick, const AudioAttributes *audioAttributes) {
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
            auto hue = static_cast<uint32_t>(randomNumberGenerator.generate(361));
            while (abs(static_cast<int>(hue - lastColor.getHue())) < 30) {
                hue = static_cast<uint32_t>(randomNumberGenerator.generate(361));
            }
            auto color = HSLColor{hue, 100, 50};
            lastColor = color;
            if (mode == 0) {
                auto index = randomNumberGenerator.generate(ledMatrix.getLedCount());
                actions.emplace_back(make_unique<Ripple>(tick, ledMatrix, index, color, 0.3));
            } else if (mode == 1) {
                actions.emplace_back(make_unique<Ripple>(tick, ledMatrix, 0, color, 0.3));
                actions.emplace_back(make_unique<Ripple>(tick, ledMatrix, ledMatrix.getLedCount() - 1, color, 0.3));
            } else if (mode == 2) {
                auto index = lastIndex + 5;
                if (index > ledMatrix.getLedCount() - 1) {
                    index = 0;
                }
                actions.emplace_back(make_unique<Ripple>(tick, ledMatrix, index, color, 0.3));
                lastIndex = index;
            } else {
                actions.emplace_back(make_unique<Ripple>(tick, ledMatrix, 30, color, 0.3));
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
