#include <chrono>
#include <thread>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "Config.h"
#include "ledMatrix/Ws2812bLedMatrix.h"

int main() {
    spdlog::stdout_color_mt(LOGGER_NAME);
    auto ledMatrix = make_unique<Ws2812bLedMatrix>(18, 0, 60);
    ledMatrix->clear();
    bool flip = true;
    for (int times = 0; times < 20; times++) {
        if (flip) {
            for (int index = 0; index < ledMatrix->getLedCount(); index++) {
                auto hue = static_cast<uint32_t >(index * 6);
                ledMatrix->modifyLed(index, HSLColor{hue, 100, 50});
                ledMatrix->render();
                std::this_thread::sleep_for(std::chrono::microseconds(TICK_INTERVAL_MICROSECONDS));
            }
        } else {
            for (int index = ledMatrix->getLedCount() - 1; index >= 0; index--) {
                auto hue = static_cast<uint32_t >(index * 6);
                ledMatrix->modifyLed(index, HSLColor{hue, 100, 50});
                ledMatrix->render();
                std::this_thread::sleep_for(std::chrono::microseconds(TICK_INTERVAL_MICROSECONDS));
            }
        }
        ledMatrix->clear();
        flip = !flip;
    }
    ledMatrix->clear();
}
