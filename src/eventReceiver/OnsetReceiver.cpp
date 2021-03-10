#include "OnsetReceiver.h"

namespace performer {

std::unique_ptr<OnsetReceiver> OnsetReceiver::create(zmq::context_t &context, const std::string &inputEndpoint) {
    auto socket = std::make_unique<impresarioUtils::NetworkSocket>(context, inputEndpoint, zmq::socket_type::sub,
                                                                   false);
    socket->setSubscriptionFilter(static_cast<std::string>(ONSET_SUBSCRIPTION_FILTER));
    return std::make_unique<OnsetReceiver>(move(socket));
}

OnsetReceiver::OnsetReceiver(std::unique_ptr<impresarioUtils::NetworkSocket> inputSocket)
        : inputSocket{move(inputSocket)} {

}

std::unique_ptr<std::vector<std::unique_ptr<Event>>> OnsetReceiver::receive() {
    auto events = std::make_unique<std::vector<std::unique_ptr<Event>>>();
    auto moreDataToCollect = true;
    while (moreDataToCollect) {
        auto buffer = inputSocket->receiveBuffer(zmq::recv_flags::dontwait);
        if (buffer != nullptr) {
            auto event = std::make_unique<OnsetEvent>(move(buffer));
            events->push_back(move(event));
        } else {
            moreDataToCollect = false;
        }
    }
    return events;
}

}
