#include "HSLColor.h"
using namespace Color;

HSLColor::HSLColor(uint32_t hue, uint8_t saturation, uint8_t lightness)
        : hue{hue},
          saturation{saturation},
          lightness{lightness} {
    if (hue > 360 || saturation > 100 || lightness > 100) {
        spdlog::get(static_cast<string>(LOGGER_NAME))->error(
                "invalid HSL Color: ({}, {}, {})", hue, saturation, lightness
        );
        throw out_of_range("invalid HSL color");
    }
}

RGBColor HSLColor::convertToRGB() const {
    auto workingHue = static_cast<float>(hue);
    auto workingSaturation = static_cast<float>(saturation) / 100;
    auto workingLightness = static_cast<float>(lightness) / 100;
    auto hDabba = workingHue / 60.0f;
    auto chroma = (1.0f - abs(2.0f * workingLightness - 1.0f)) * workingSaturation;
    auto intermediary = chroma * (1.0f - abs(fmod(hDabba, 2.0f) - 1.0f));
    auto lightnessAdjustment = workingLightness - chroma / 2.0f;
    float initialRed, initialGreen, initialBlue;
    if (0.0f <= hDabba && hDabba <= 1.0f) {
        initialRed = chroma;
        initialGreen = intermediary;
        initialBlue = 0.0f;
    } else if (1.0f <= hDabba && hDabba <= 2.0f) {
        initialRed = intermediary;
        initialGreen = chroma;
        initialBlue = 0.0f;
    } else if (2.0f <= hDabba && hDabba <= 3.0f) {
        initialRed = 0.0f;
        initialGreen = chroma;
        initialBlue = intermediary;
    } else if (3.0f <= hDabba && hDabba <= 4.0f) {
        initialRed = 0.0f;
        initialGreen = intermediary;
        initialBlue = chroma;
    } else if (4.0f <= hDabba && hDabba <= 5.0f) {
        initialRed = intermediary;
        initialGreen = 0.0f;
        initialBlue = chroma;
    } else {
        initialRed = chroma;
        initialGreen = 0.0f;
        initialBlue = intermediary;
    }
    auto red = static_cast<uint8_t>(roundf((initialRed + lightnessAdjustment) * 255));
    auto green = static_cast<uint8_t>(roundf((initialGreen + lightnessAdjustment) * 255));
    auto blue = static_cast<uint8_t>(roundf((initialBlue + lightnessAdjustment) * 255));
    return RGBColor{red, green, blue};
}
