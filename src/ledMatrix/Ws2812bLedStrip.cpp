#include "Ws2812bLedStrip.h"

namespace performer {

Ws2812bLedStrip::Ws2812bLedStrip()
        : ledDriver{},
          pwmChannel{Config::getInstance().getPwmChannel()},
        // the extra multiplier on height is a workaround for an unknown issue in the library, try removing in the future
          ledCount{Config::getInstance().getLedMatrixWidth() * Config::getInstance().getledMatrixHeight() + 2},
          maxBrightness{Config::getInstance().getMaxBrightness()} {
    ledDriver.freq = WS2811_TARGET_FREQ;
    ledDriver.dmanum = Config::getInstance().getDmaChannel();
    int unusedPwmChannel;
    if (pwmChannel == 0) {
        ledDriver.channel[pwmChannel].gpionum = 18;
        unusedPwmChannel = 1;
    } else if (pwmChannel == 1) {
        ledDriver.channel[pwmChannel].gpionum = 13;
        unusedPwmChannel = 0;
    } else {
        std::ostringstream errorMessage;
        errorMessage << "invalid pwm channel: " << pwmChannel;
        throw std::out_of_range(errorMessage.str());
    }
    ledDriver.channel[pwmChannel].count = ledCount;
    ledDriver.channel[pwmChannel].invert = 0;
    ledDriver.channel[pwmChannel].strip_type = WS2812_STRIP;
    ledDriver.channel[pwmChannel].brightness = Config::getInstance().getInitialBrightness();
    ledDriver.channel[unusedPwmChannel].gpionum = 0;
    ledDriver.channel[unusedPwmChannel].count = 0;
    ledDriver.channel[unusedPwmChannel].invert = 0;
    ledDriver.channel[unusedPwmChannel].strip_type = 0;
    ledDriver.channel[unusedPwmChannel].brightness = 0;
    ws2811_init(&ledDriver);
}

Ws2812bLedStrip::~Ws2812bLedStrip() {
    ws2811_fini(&ledDriver);
}

void Ws2812bLedStrip::render() {
    ws2811_render(&ledDriver);
}

void Ws2812bLedStrip::setLed(int index, const RGBColor &color) {
    ledDriver.channel[pwmChannel].leds[index] = formatColorForDriver(color);
}

void Ws2812bLedStrip::setBrightness(int brightness) {
    if (brightness < maxBrightness) {
        ledDriver.channel[pwmChannel].brightness = brightness;
    }
}

uint32_t Ws2812bLedStrip::formatColorForDriver(const RGBColor &color) {
    auto result = static_cast<uint32_t>(color.red);
    result <<= 0x8u;
    result |= static_cast<uint32_t>(color.green);
    result <<= 0x8u;
    result |= static_cast<uint32_t>(color.blue);
    return result;
}

}
