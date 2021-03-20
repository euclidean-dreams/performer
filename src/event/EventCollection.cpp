#include "event/EventCollection.h"

namespace performer {

EventCollection::EventCollection()
        : events{} {

}

void EventCollection::pushEvent(std::unique_ptr<const Event> event) {
    events.push_front(move(event));
}

bool EventCollection::moreEventsLeft() const {
    return !events.empty();
}

std::unique_ptr<const Event> EventCollection::popEvent() {
    auto result = move(events.back());
    events.pop_back();
    return result;
}

}
