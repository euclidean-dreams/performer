#include "Ws2812bLedStripRenderer.h"

namespace performer {

void Ws2812bLedStripRenderer::startRenderLoop(std::unique_ptr<Ws2812bLedStripRenderer> ledMatrixRenderer) {
    while (!ledMatrixRenderer->finished()) {
        ledMatrixRenderer->render();
    }
}

Ws2812bLedStripRenderer::Ws2812bLedStripRenderer(std::unique_ptr<Ws2812bLedStrip> ledStrip,
                                                 std::shared_ptr<LedMatrixProxy> ledMatrixProxy)
        : ledStrip{move(ledStrip)},
          ledMatrixProxy{move(ledMatrixProxy)},
          refreshRate{Config::getInstance().getRefreshRate()} {
    if (this->ledMatrixProxy->height() * this->ledMatrixProxy->width() != this->ledStrip->size()) {
        throw std::invalid_argument("led proxy is a different size than the led strip it is attempting to proxy");
    }

}

void Ws2812bLedStripRenderer::render() {
    auto cycleStartTime = impresarioUtils::getCurrentTime();
    update();
    auto totalCycleTime = impresarioUtils::getElapsedTime(cycleStartTime);
    if (refreshRate > totalCycleTime) {
        std::this_thread::sleep_for(std::chrono::microseconds(refreshRate - totalCycleTime));
    }
    ledStrip->render();
}

void Ws2812bLedStripRenderer::update() {
    auto lock = ledMatrixProxy->acquireLock();
    for (int y = 0; y < ledMatrixProxy->height(); y++) {
        for (int x = 0; x < ledMatrixProxy->width(); x++) {
            auto index = y * ledMatrixProxy->width() + x;
            auto color = ledMatrixProxy->getLed(x, y).convertToRGB();
            ledStrip->setLed(index, color);
        }
    }
}

bool Ws2812bLedStripRenderer::finished() {
    return false;
}

}
