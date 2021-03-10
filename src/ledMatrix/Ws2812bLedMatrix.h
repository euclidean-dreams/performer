#ifndef PERFORMER_WS2812BLEDMATRIX_H
#define PERFORMER_WS2812BLEDMATRIX_H

#include <sstream>
#include <ws2811.h>
#include "Config.h"
#include "ledMatrix/LedMatrix.h"

namespace performer {

class Ws2812bLedMatrix : public LedMatrix {
private:
    ws2811_t ledDriver;
    int pwmChannel;
    int ledCount;

    inline static uint32_t formatColorForDriver(const ImpresarioSerialization::RGBColor *color);

public:
    Ws2812bLedMatrix(int gpioNum, int pwmChannel, int ledCount);

    ~Ws2812bLedMatrix() override;

    void render() override;

    void consumeLedPacket(const ImpresarioSerialization::LedPacket *ledPacket) override;
};

}

#endif //PERFORMER_WS2812BLEDMATRIX_H
