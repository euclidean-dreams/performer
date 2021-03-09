#include "OnsetReceiver.h"

std::unique_ptr<OnsetReceiver> OnsetReceiver::create(context_t &context, const string &inputEndpoint) {
    auto socket = make_unique<NetworkSocket>(context, inputEndpoint, socket_type::sub, false);
    socket->setSubscriptionFilter(static_cast<string>(ONSET_SUBSCRIPTION_FILTER));
    return make_unique<OnsetReceiver>(move(socket));
}

OnsetReceiver::OnsetReceiver(std::unique_ptr<NetworkSocket> inputSocket)
        : inputSocket{move(inputSocket)} {

}

std::unique_ptr<vector<std::unique_ptr<Event>>> OnsetReceiver::receive() {
    auto events = make_unique<vector<std::unique_ptr<Event>>>();
    auto moreDataToCollect = true;
    while (moreDataToCollect) {
        auto buffer = inputSocket->receiveBuffer(recv_flags::dontwait);
        if (buffer != nullptr) {
            auto event = make_unique<OnsetEvent>(move(buffer));
            events->push_back(move(event));
        } else {
            moreDataToCollect = false;
        }
    }
    return events;
}
