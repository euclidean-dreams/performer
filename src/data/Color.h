#ifndef PERFORMER_COLOR_H
#define PERFORMER_COLOR_H

#include <cstdint>
#include <spdlog/spdlog.h>
#include "Config.h"

struct RGBColor {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    inline bool operator==(const RGBColor &other) const {
        return red == other.red && green == other.green && blue == other.blue;
    }

    inline bool operator!=(const RGBColor &other) const {
        if (*this == other) {
            return false;
        } else {
            return true;
        }
    }
};

struct HSLColor {
    uint32_t hue;
    uint8_t saturation;
    uint8_t lightness;

    inline bool operator==(const HSLColor &other) const {
        return hue == other.hue && saturation == other.saturation && lightness == other.lightness;
    }

    inline bool operator!=(const HSLColor &other) const {
        if (*this == other) {
            return false;
        } else {
            return true;
        }
    }
};

RGBColor convertHSLToRGB(const HSLColor &color) {
    if (color.hue > 360 || color.saturation > 100 || color.lightness > 100) {
        spdlog::get(LOGGER_NAME)->error(
                "invalid HSL Color: ({}, {}, {}) - could not convert to RGB",
                color.hue, color.saturation, color.lightness
        );
        throw out_of_range("invalid HSL color");
    }
    auto hue = static_cast<float>(color.hue);
    auto saturation = static_cast<float>(color.saturation) / 100;
    auto lightness = static_cast<float>(color.lightness) / 100;
    auto hDabba = hue / 60.0f;
    auto chroma = (1.0f - abs(2.0f * lightness - 1.0f)) * saturation;
    auto intermediary = chroma * (1.0f - abs(fmod(hDabba, 2.0f) - 1.0f));
    auto lightnessAdjustment = lightness - chroma / 2.0f;
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
    auto red = static_cast<uint8_t>(round((initialRed + lightnessAdjustment) * 255));
    auto green = static_cast<uint8_t>(round((initialGreen + lightnessAdjustment) * 255));
    auto blue = static_cast<uint8_t>(round((initialBlue + lightnessAdjustment) * 255));
    return {red, green, blue};
}

#endif //PERFORMER_COLOR_H
