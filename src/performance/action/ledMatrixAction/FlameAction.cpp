#include "FlameAction.h"

namespace performer {

FlameAction::FlameAction(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                         Coordinate origin, HSLColor color, int width, int height, int mode)
        : LedMatrixAction(ledMatrix),
          randomNumberGenerator{randomNumberGenerator},
          currentLightness{static_cast<float>(color.getLightness())},
          ramping{true} {
    auto flameCount = 2;
    for (int index = 0; index < flameCount; index++) {
        int hue = 0;
        if (mode == 0) {
            hue = color.getHue() + index * 10;
        } else if (mode == 1) {
            hue = color.getHue() + index * 80 + randomNumberGenerator.generate(30);
        } else if (mode == 2) {
            hue = randomNumberGenerator.generate(HSL_HUE_MAX);
        }
        auto currentColor = HSLColor{LedGizmos::bindHue(hue), color.getSaturation(), color.getLightness()};
        auto currentHeight = height - index * height / flameCount;
        auto currentWidth = width - index * height / flameCount;
        flameStack.push_back(
                std::make_unique<Flame>(origin, currentColor, currentWidth, currentHeight)
        );
    }
}

bool FlameAction::finished() {
    return currentLightness == 0;
}

void FlameAction::handleTick() {
    if (ramping) {
        currentLightness += 20;
        if (currentLightness > 50) {
            currentLightness = 50;
            ramping = false;
        }
    } else {
        currentLightness--;
        if (currentLightness < 0) {
            currentLightness = 0;
        }
    }
    for (auto &flame: flameStack) {
        flame->render(ledMatrix);
        auto currentColor = flame->getRootColor();
        flame->setRootColor(
                {currentColor.getHue(), currentColor.getSaturation(), static_cast<uint8_t>(currentLightness)}
        );
    }
    flicker(0.7);
}

void FlameAction::flicker(float intensity) {
    for (auto &flame: flameStack) {
        flame->flicker(randomNumberGenerator, intensity);
    }
}

}
