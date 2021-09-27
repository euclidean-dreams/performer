#include "Bootstrapper.h"

namespace performer {

void Bootstrapper::boot() {
    Config::initialize();
    auto config = Config::getInstance();
    spdlog::stdout_color_mt(config.getLoggerName());
    zmq::context_t context(1);

    // led renderer
    auto ws2812BLedStrip = std::make_unique<Ws2812bLedStrip>();
    auto ledMatrixProxy = std::make_shared<LedMatrixProxy>(config.getLedMatrixWidth(), config.getledMatrixHeight());
    auto ws2812BLedStripRenderer = std::make_unique<Ws2812bLedStripRenderer>(move(ws2812BLedStrip), ledMatrixProxy);
    std::thread ledMatrixRenderingThread{Ws2812bLedStripRenderer::startRenderLoop, move(ws2812BLedStripRenderer)};

    // packet receivers
    auto conductorSocket = std::make_unique<impresarioUtils::NetworkSocket>(
            context,
            config.getConductorEndpoint(),
            zmq::socket_type::sub,
            false
    );
    conductorSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::displaySignal);
    auto conductorPacketReceiver = std::make_unique<impresarioUtils::PacketReceiver>(move(conductorSocket));

    auto fasciaSocket = std::make_unique<impresarioUtils::NetworkSocket>(
            context,
            config.getFasciaEndpoint(),
            zmq::socket_type::sub,
            false
    );
    fasciaSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::floatMorsel);
    fasciaSocket->setSubscriptionFilter(ImpresarioSerialization::Identifier::floatArrayMorsel);
    auto fasciaPacketReceiver = std::make_unique<impresarioUtils::PacketReceiver>(move(fasciaSocket));

    auto packetReceivers = std::make_unique<std::vector<std::unique_ptr<impresarioUtils::PacketReceiver>>>();
    packetReceivers->push_back(move(conductorPacketReceiver));
    packetReceivers->push_back(move(fasciaPacketReceiver));

    // led performance
    auto ledPerformance = std::make_unique<LedPerformance>(move(packetReceivers), ledMatrixProxy);
    std::thread ledPerformanceThread{LedPerformance::startPerformanceLoop, move(ledPerformance)};

    ledPerformanceThread.join();
    ledMatrixRenderingThread.join();
}

}
