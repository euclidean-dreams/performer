#include "TimelineManager.h"

namespace performer {

TimelineManager::TimelineManager()
        : timelineSize{TIMELINE_SIZE},
          onsetTimeline{timelineSize},
          pitchTimeline{timelineSize} {

}

void TimelineManager::addEvent(std::unique_ptr<const Event> event) {
    if (event->getIdentifier() == ImpresarioSerialization::Identifier::onset) {
        onsetTimeline.addEvent(move(event));
    } else if (event->getIdentifier() == ImpresarioSerialization::Identifier::pitch) {
        pitchTimeline.addEvent(move(event));
    }
}

const OnsetTimeline &TimelineManager::getOnsetTimeline() const {
    return onsetTimeline;
}

const PitchTimeline &TimelineManager::getPitchTimeline() const {
    return pitchTimeline;
}

int TimelineManager::getTimelineSize() const {
    return static_cast<int>(timelineSize);
}

}
