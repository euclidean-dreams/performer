#ifndef PERFORMER_WS2812BLEDMATRIX_H
#define PERFORMER_WS2812BLEDMATRIX_H

#include <spdlog/spdlog.h>
#include <ws2811.h>
#include "Config.h"
#include "LedMatrix.h"

using namespace std;

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

    void consumeLedPacket(const LedPacket *ledPacket) override;
};

#endif //PERFORMER_WS2812BLEDMATRIX_H
