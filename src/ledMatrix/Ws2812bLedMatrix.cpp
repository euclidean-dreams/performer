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
        spdlog::get(static_cast<string>(LOGGER_NAME))->error("invalid pwm channel: {}", pwmChannel);
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

void Ws2812bLedMatrix::render() {
    ws2811_render(&ledDriver);
}

void Ws2812bLedMatrix::consumeLedPacket(const LedPacket *ledPacket) {
    if (ledPacket == nullptr) {
        spdlog::get(static_cast<string>(LOGGER_NAME))->error("led matrix received a null led packet");
        throw invalid_argument("led matrix received a null led packet");
    }
    auto leds = ledPacket->leds();
    if (leds->size() != ledCount) {
        spdlog::get(static_cast<string>(LOGGER_NAME))->error(
                "led matrix received an improperly sized led packet of size: {}", leds->size()
        );
        throw invalid_argument("led matrix received an improperly sized led packet");
    }
    for (int index = 0; index < leds->size(); index++) {
        auto rawColor = (*leds)[index];
        ledDriver.channel[pwmChannel].leds[index] = formatColorForDriver(rawColor);
    }
}

uint32_t Ws2812bLedMatrix::formatColorForDriver(const ImpresarioSerialization::RGBColor *color) {
    auto result = static_cast<uint32_t>(color->red());
    result <<= 0x8u;
    result |= static_cast<uint32_t>(color->green());
    result <<= 0x8u;
    result |= static_cast<uint32_t>(color->blue());
    return result;
}