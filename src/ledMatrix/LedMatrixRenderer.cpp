#include "LedMatrixRenderer.h"

LedMatrixRenderer::LedMatrixRenderer(std::unique_ptr<LedMatrix> ledMatrix,
                                     std::unique_ptr<NetworkSocket> inputSocket)
        : ledMatrix{move(ledMatrix)},
          inputSocket{move(inputSocket)} {

}

void LedMatrixRenderer::render() {
    auto cycleStartTime = getCurrentTime();
    auto buffer = receiveLedPacketBuffer();
    auto ledPacket = GetLedPacket(buffer.get());
    ledMatrix->consumeLedPacket(ledPacket);
    auto totalCycleTime = getElapsedTime(cycleStartTime);
    if (TICK_INTERVAL_MICROSECONDS > totalCycleTime) {
        this_thread::sleep_for(microseconds(TICK_INTERVAL_MICROSECONDS - totalCycleTime));
    }
    ledMatrix->render();
}

std::unique_ptr<char[]> LedMatrixRenderer::receiveLedPacketBuffer() {
    auto request = multipart_t{};
    request.addmem(nullptr, 0);
    inputSocket->send(request);
    return inputSocket->receiveBuffer();
}

bool LedMatrixRenderer::finished() {
    return false;
}

void LedMatrixRenderer::startRenderLoop(LedMatrixRenderer &ledMatrixRenderer) {
    while (!ledMatrixRenderer.finished()) {
        ledMatrixRenderer.render();
    }
}

