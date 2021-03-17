#include "OnsetTimeline.h"

namespace performer {

OnsetTimeline::OnsetTimeline(unsigned int maxSize)
        : maxSize{maxSize},
          events{},
          timeline{} {

}

void OnsetTimeline::pushEvent(std::unique_ptr<const Event> event) {
    if (timeline.size() >= maxSize) {
        timeline.pop_back();
        events.pop_back();
    }
    timeline.push_front(event->getOnset());
    events.push_front(move(event));
}

std::list<const ImpresarioSerialization::Onset *>::const_iterator OnsetTimeline::begin() const {
    return timeline.cbegin();
}

std::list<const ImpresarioSerialization::Onset *>::const_iterator OnsetTimeline::end() const {
    return timeline.cend();
}
}
