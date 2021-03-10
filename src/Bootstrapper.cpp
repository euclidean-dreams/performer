#include "Bootstrapper.h"

namespace performer {

void Bootstrapper::boot() {
    spdlog::stdout_color_mt(static_cast<std::string>(LOGGER_NAME));
    zmq::context_t context(1);

    auto rendererEndpoint = "inproc://ledMatrixRenderer";
    auto ledMatrix = std::make_unique<Ws2812bLedMatrix>(18, 0, LED_COUNT);
    auto ledMatrixRendererSocket = std::make_unique<impresarioUtils::NetworkSocket>(context, rendererEndpoint,
                                                                                    zmq::socket_type::pair, true);
    LedMatrixRenderer ledMatrixRenderer{move(ledMatrix), move(ledMatrixRendererSocket)};
    std::thread ledMatrixRenderingThread{LedMatrixRenderer::startRenderLoop, std::ref(ledMatrixRenderer)};

    auto onsetReceiver = OnsetReceiver::create(context, static_cast<std::string>(CONDUCTOR_ENDPOINT));
    auto ledPerformancePacketSocket = std::make_unique<impresarioUtils::NetworkSocket>(context, rendererEndpoint,
                                                                                       zmq::socket_type::pair,
                                                                                       false);
    LedPerformance ledPerformance{move(onsetReceiver), move(ledPerformancePacketSocket), LED_COUNT};

    while (true) {
        ledPerformance.perform();
    }
    ledMatrixRenderingThread.join();

}

}
