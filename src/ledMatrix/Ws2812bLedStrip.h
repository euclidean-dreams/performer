#ifndef PERFORMER_WS2812BLEDSTRIP_H
#define PERFORMER_WS2812BLEDSTRIP_H

#include <ws2811.h>
#include "Config.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class Ws2812bLedStrip : impresarioUtils::NonCopyable {
private:
    ws2811_t ledDriver;
    int pwmChannel;
    int ledCount;
    int maxBrightness;

    inline static uint32_t formatColorForDriver(const RGBColor &color);

public:
    Ws2812bLedStrip();

    ~Ws2812bLedStrip();

    void render();

    void setLed(int index, const RGBColor &color);

    void setBrightness(int brightness);

    int size() { return ledCount; }
};

}

#endif //PERFORMER_WS2812BLEDSTRIP_H
