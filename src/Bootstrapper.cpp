#include "Bootstrapper.h"

namespace performer {

void Bootstrapper::boot() {
    spdlog::stdout_color_mt(static_cast<std::string>(LOGGER_NAME));
    zmq::context_t context(1);

    // led renderer
    auto ledMatrix = std::make_unique<Ws2812bLedMatrix>(13, 1, LED_COUNT);
    auto ledMatrixProxy = std::make_shared<LedMatrixProxy>(LED_COUNT);
    auto ledMatrixRenderer = std::make_unique<LedMatrixRenderer>(move(ledMatrix), ledMatrixProxy);
    std::thread ledMatrixRenderingThread{LedMatrixRenderer::startRenderLoop, move(ledMatrixRenderer)};

    // event receiver
    auto eventReceiverSocket = std::make_unique<impresarioUtils::NetworkSocket>(context,
                                                                                static_cast<std::string>(CONDUCTOR_ENDPOINT),
                                                                                zmq::socket_type::sub,
                                                                                false);
    eventReceiverSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::onset);
    eventReceiverSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::pitch);
    eventReceiverSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::displaySignal);
    auto eventReceiver = std::make_unique<EventReceiver>(move(eventReceiverSocket));

    // led performance
    auto ledPerformance = std::make_unique<LedPerformance>(move(eventReceiver), ledMatrixProxy);
    std::thread ledPerformanceThread{LedPerformance::startPerformanceLoop, move(ledPerformance)};

    ledPerformanceThread.join();
    ledMatrixRenderingThread.join();
}

}
