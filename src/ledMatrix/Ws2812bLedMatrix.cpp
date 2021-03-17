#include "Ws2812bLedMatrix.h"

namespace performer {

Ws2812bLedMatrix::Ws2812bLedMatrix(int gpioNum, int pwmChannel, int ledCount)
        : ledDriver{},
          pwmChannel{pwmChannel},
          ledCount{ledCount} {
    ledDriver.freq = WS2811_TARGET_FREQ;
    int unusedPwmChannel;
    if (pwmChannel == 0) {
        unusedPwmChannel = 1;
        ledDriver.dmanum = 10;
    } else if (pwmChannel == 1) {
        unusedPwmChannel = 0;
        ledDriver.dmanum = 11;
    } else {
        std::ostringstream errorMessage;
        errorMessage << "invalid pwm channel: " << pwmChannel;
        throw std::out_of_range(errorMessage.str());
    }
    ledDriver.channel[pwmChannel].gpionum = gpioNum;
    ledDriver.channel[pwmChannel].count = ledCount;
    ledDriver.channel[pwmChannel].invert = 0;
    ledDriver.channel[pwmChannel].strip_type = WS2812_STRIP;
    ledDriver.channel[pwmChannel].brightness = LED_MATRIX_INITIAL_BRIGHTNESS;
    ledDriver.channel[unusedPwmChannel].gpionum = 0;
    ledDriver.channel[unusedPwmChannel].count = 0;
    ledDriver.channel[unusedPwmChannel].invert = 0;
    ledDriver.channel[unusedPwmChannel].strip_type = 0;
    ledDriver.channel[unusedPwmChannel].brightness = 0;
    ws2811_init(&ledDriver);
}

Ws2812bLedMatrix::~Ws2812bLedMatrix() {
    ws2811_fini(&ledDriver);
}

void Ws2812bLedMatrix::render() {
    ws2811_render(&ledDriver);
}

void Ws2812bLedMatrix::update(LedMatrixProxy &proxy) {
    auto lock = proxy.acquireLock();
    if (proxy.size() != ledCount) {
        throw std::invalid_argument("led matrix attempted to update using a proxy of invalid size");
    }
    for (int index = 0; index < ledCount; index++) {
        auto rawColor = proxy.getLed(index).convertToRGB();
        ledDriver.channel[pwmChannel].leds[index] = formatColorForDriver(rawColor);
    }
}

uint32_t Ws2812bLedMatrix::formatColorForDriver(const RGBColor &color) {
    auto result = static_cast<uint32_t>(color.red);
    result <<= 0x8u;
    result |= static_cast<uint32_t>(color.green);
    result <<= 0x8u;
    result |= static_cast<uint32_t>(color.blue);
    return result;
}

}
