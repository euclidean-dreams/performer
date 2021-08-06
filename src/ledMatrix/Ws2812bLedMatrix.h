#ifndef PERFORMER_WS2812BLEDMATRIX_H
#define PERFORMER_WS2812BLEDMATRIX_H

#include <ws2811.h>
#include "ledMatrix/LedMatrix.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class Ws2812bLedMatrix : public LedMatrix {
private:
    inline static const int LED_MATRIX_INITIAL_BRIGHTNESS = 50;

    ws2811_t ledDriver;
    int pwmChannel;
    int ledCount;

    inline static uint32_t formatColorForDriver(const RGBColor &color);

public:
    Ws2812bLedMatrix(int gpioNum, int pwmChannel, int ledCount);

    ~Ws2812bLedMatrix() override;

    void render() override;

    void update(LedMatrixProxy &proxy) override;
};

}

#endif //PERFORMER_WS2812BLEDMATRIX_H
