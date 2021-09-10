#include "LedMatrixRenderer.h"

namespace performer {

void LedMatrixRenderer::startRenderLoop(std::unique_ptr<LedMatrixRenderer> ledMatrixRenderer) {
    while (!ledMatrixRenderer->finished()) {
        ledMatrixRenderer->render();
    }
}

LedMatrixRenderer::LedMatrixRenderer(std::unique_ptr<LedMatrix> ledMatrix,
                                     std::shared_ptr<LedMatrixProxy> ledMatrixProxy)
        : ledMatrix{move(ledMatrix)},
          ledMatrixProxy{move(ledMatrixProxy)} {

}

void LedMatrixRenderer::render() {
    auto cycleStartTime = impresarioUtils::getCurrentTime();
    ledMatrix->update(*ledMatrixProxy);
    auto totalCycleTime = impresarioUtils::getElapsedTime(cycleStartTime);
    if (TICK_INTERVAL_MICROSECONDS > totalCycleTime) {
        std::this_thread::sleep_for(std::chrono::microseconds(TICK_INTERVAL_MICROSECONDS - totalCycleTime));
    }
    ledMatrix->render();
}

bool LedMatrixRenderer::finished() {
    return false;
}

}
