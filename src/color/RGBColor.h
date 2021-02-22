#ifndef PERFORMER_RGBCOLOR_H
#define PERFORMER_RGBCOLOR_H

#include <cstdint>

class RGBColor {
private:
    uint8_t red;
    uint8_t green;
    uint8_t blue;

public:
    RGBColor(uint8_t red, uint8_t green, uint8_t blue) : red{red}, green{green}, blue{blue} {}

    inline uint8_t getRed() const { return red; }

    inline uint8_t getGreen() const { return green; }

    inline uint8_t getBlue() const { return blue; }
};

#endif //PERFORMER_RGBCOLOR_H
