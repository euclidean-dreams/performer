#include "OnsetReceiver.h"

OnsetReceiver OnsetReceiver::create(context_t context, const string &inputEndpoint, const string &subscriptionFilter) {
    auto socket = make_unique<NetworkSocket>(context, inputEndpoint, socket_type::sub, false);
    socket->setSubscriptionFilter(subscriptionFilter);
    return OnsetReceiver(move(socket));
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
            events->emplace_back(make_unique<OnsetEvent>(move(buffer)));
        } else {
            moreDataToCollect = false;
        }
    }
    return events;
}
