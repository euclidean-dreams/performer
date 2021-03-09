#include <zmq.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "NetworkSocket.h"
#include "Config.h"
#include "performance/LedPerformance.h"
#include "ledMatrix/LedMatrixRenderer.h"
#include "ledMatrix/Ws2812bLedMatrix.h"

using namespace zmq;

int main() {
    spdlog::stdout_color_mt(static_cast<string>(LOGGER_NAME));
    context_t context(1);

    auto rendererEndpoint = "inproc://ledMatrixRenderer";
    auto ledMatrix = make_unique<Ws2812bLedMatrix>(18, 0, LED_COUNT);
    auto ledMatrixRendererSocket = make_unique<NetworkSocket>(context, rendererEndpoint, socket_type::pair, true);
    LedMatrixRenderer ledMatrixRenderer{move(ledMatrix), move(ledMatrixRendererSocket)};
    thread ledMatrixRenderingThread{LedMatrixRenderer::startRenderLoop, ref(ledMatrixRenderer)};

    auto onsetReceiver = OnsetReceiver::create(context, static_cast<string>(CONDUCTOR_ENDPOINT));
    auto ledPerformancePacketSocket = make_unique<NetworkSocket>(context, rendererEndpoint, socket_type::pair, false);
    LedPerformance ledPerformance{move(onsetReceiver), move(ledPerformancePacketSocket), LED_COUNT};

    while (true) {
        ledPerformance.perform();
    }
    ledMatrixRenderingThread.join();
}
