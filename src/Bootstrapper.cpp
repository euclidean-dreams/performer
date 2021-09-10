#include "Bootstrapper.h"

namespace performer {

void Bootstrapper::boot() {
    spdlog::stdout_color_mt(static_cast<std::string>(LOGGER_NAME));
    zmq::context_t context(1);

    // led renderer
    auto ledMatrix = std::make_unique<Ws2812bLedMatrix>(18, 0, LED_COUNT);
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
    auto morselSocket = std::make_unique<impresarioUtils::NetworkSocket>(context, "tcp://0.0.0.0:44449",
                                                                         zmq::socket_type::sub, true);
    morselSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::floatMorsel);
    morselSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::floatArrayMorsel);
    auto ledPerformance = std::make_unique<LedPerformance>(move(eventReceiver), ledMatrixProxy, move(morselSocket));
    std::thread ledPerformanceThread{LedPerformance::startPerformanceLoop, move(ledPerformance)};

    ledPerformanceThread.join();
    ledMatrixRenderingThread.join();
}

}
