#include "PitchTimeline.h"

namespace performer {

PitchTimeline::PitchTimeline(unsigned int maxSize)
        : maxSize{maxSize},
          events{},
          timeline{} {

}

void PitchTimeline::pushEvent(std::unique_ptr<const Event> event) {
    if (timeline.size() >= maxSize) {
        timeline.pop_back();
        events.pop_back();
    }
    timeline.push_front(event->getPitch());
    events.push_front(move(event));
}

std::list<const ImpresarioSerialization::Pitch *>::const_iterator PitchTimeline::begin() const {
    return timeline.cbegin();
}

std::list<const ImpresarioSerialization::Pitch *>::const_iterator PitchTimeline::end() const {
    return timeline.cend();
}

}
