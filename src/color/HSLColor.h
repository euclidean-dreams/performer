#ifndef PERFORMER_HSLCOLOR_H
#define PERFORMER_HSLCOLOR_H

#include <cstdint>
#include <spdlog/spdlog.h>
#include "Config.h"
#include "RGBColor.h"

class HSLColor {
private:
    uint32_t hue;
    uint8_t saturation;
    uint8_t lightness;

public:
    HSLColor(uint32_t hue, uint8_t saturation, uint8_t lightness);

    inline uint32_t getHue() const { return hue; }

    inline uint8_t getSaturation() const { return saturation; }

    inline uint8_t getLightness() const { return lightness; }

    RGBColor convertToRGB() const;
};

#endif //PERFORMER_HSLCOLOR_H
