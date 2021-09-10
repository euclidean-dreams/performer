#include "event/EventReceiver.h"

namespace performer {

EventReceiver::EventReceiver(std::unique_ptr<impresarioUtils::NetworkSocket> input)
        : input{move(input)} {

}

std::unique_ptr<EventCollection> EventReceiver::receive() {
    auto events = std::make_unique<EventCollection>();
    auto moreDataToCollect = true;
    while (moreDataToCollect) {
        auto serializedData = input->receiveSerializedData(zmq::recv_flags::dontwait);
        if (serializedData != nullptr) {
            auto event = std::make_unique<Event>(move(serializedData));
            events->pushEvent(move(event));
        } else {
            moreDataToCollect = false;
        }
    }
    return events;
}

}
