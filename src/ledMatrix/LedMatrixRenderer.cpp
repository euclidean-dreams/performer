#include "LedMatrixRenderer.h"

namespace performer {

void LedMatrixRenderer::startRenderLoop(LedMatrixRenderer &ledMatrixRenderer) {
    while (!ledMatrixRenderer.finished()) {
        ledMatrixRenderer.render();
    }
}

LedMatrixRenderer::LedMatrixRenderer(std::unique_ptr<LedMatrix> ledMatrix,
                                     std::unique_ptr<impresarioUtils::NetworkSocket> inputSocket)
        : ledMatrix{move(ledMatrix)},
          inputSocket{move(inputSocket)} {

}

void LedMatrixRenderer::render() {
    auto cycleStartTime = impresarioUtils::getCurrentTime();
    auto buffer = receiveLedPacketBuffer();
    auto ledPacket = ImpresarioSerialization::GetLedPacket(buffer.get());
    ledMatrix->consumeLedPacket(ledPacket);
    auto totalCycleTime = impresarioUtils::getElapsedTime(cycleStartTime);
    if (TICK_INTERVAL_MICROSECONDS > totalCycleTime) {
        std::this_thread::sleep_for(std::chrono::microseconds(TICK_INTERVAL_MICROSECONDS - totalCycleTime));
    }
    ledMatrix->render();
}

std::unique_ptr<char[]> LedMatrixRenderer::receiveLedPacketBuffer() {
    auto request = zmq::multipart_t{};
    request.addmem(nullptr, 0);
    inputSocket->send(request);
    return inputSocket->receiveBuffer();
}

bool LedMatrixRenderer::finished() {
    return false;
}

}
