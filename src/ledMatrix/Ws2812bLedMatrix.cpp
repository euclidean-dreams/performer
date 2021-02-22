#include "Ws2812bLedMatrix.h"

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
        spdlog::get(LOGGER_NAME)->error("invalid pwm channel: {}", pwmChannel);
        throw out_of_range("invalid pwm channel");
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

uint32_t Ws2812bLedMatrix::formatColorForDriver(const RGBColor &color) {
    auto result = static_cast<uint32_t>(color.getRed());
    result <<= 0x8u;
    result |= static_cast<uint32_t>(color.getGreen());
    result <<= 0x8u;
    result |= static_cast<uint32_t>(color.getBlue());
    return result;
}

void Ws2812bLedMatrix::render() {
    ws2811_render(&ledDriver);
}

void Ws2812bLedMatrix::clear() {
    for (int index = 0; index < ledCount; index++) {
        modifyLed(index, RGBColor{0, 0, 0});
    }
    render();
}

void Ws2812bLedMatrix::modifyLed(int index, HSLColor color) {
    modifyLed(index, color.convertToRGB());
}

void Ws2812bLedMatrix::modifyLed(int index, RGBColor color) {
    if (index < 0 || index > ledCount) {
        spdlog::get(LOGGER_NAME)->error("attempted to modify an led at an invalid index: {}", index);
        throw out_of_range("attempted to modify an led at an invalid index");
    }
    ledDriver.channel[pwmChannel].leds[index] = formatColorForDriver(color);
}

int Ws2812bLedMatrix::getLedCount() const {
    return ledCount;
}

