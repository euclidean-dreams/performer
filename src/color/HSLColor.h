#ifndef PERFORMER_HSLCOLOR_H
#define PERFORMER_HSLCOLOR_H

#include <cstdint>
#include <cmath>
#include <sstream>
#include <RGBColor_generated.h>

namespace performer {

class HSLColor {
private:
    uint32_t hue;
    uint8_t saturation;
    uint8_t lightness;

public:
    HSLColor(uint32_t hue, uint8_t saturation, uint8_t lightness);

    uint32_t getHue() const;

    uint8_t getSaturation() const;

    uint8_t getLightness() const;

    ImpresarioSerialization::RGBColor convertToRGB() const;
};

}

#endif //PERFORMER_HSLCOLOR_H
