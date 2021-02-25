#ifndef PERFORMER_WS2812BLEDMATRIX_H
#define PERFORMER_WS2812BLEDMATRIX_H

#include <ws2811.h>
#include "color/RGBColor.h"
#include "color/HSLColor.h"
#include "LedMatrix.h"

class Ws2812bLedMatrix : public LedMatrix {
private:
    ws2811_t ledDriver;
    int pwmChannel;
    int ledCount;

    inline static uint32_t formatColorForDriver(const RGBColor &color);

public:
    Ws2812bLedMatrix(int gpioNum, int pwmChannel, int ledCount);

    ~Ws2812bLedMatrix() override;

    void render() override;

    void clear() override;

    void modifyLed(int index, HSLColor color) override;

    void modifyLed(int index, RGBColor color) override;

    int getLedCount() const override;
};

#endif //PERFORMER_WS2812BLEDMATRIX_H
