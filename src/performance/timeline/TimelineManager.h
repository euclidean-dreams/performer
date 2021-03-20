#ifndef PERFORMER_TIMELINEMANAGER_H
#define PERFORMER_TIMELINEMANAGER_H

#include <list>
#include <memory>
#include "event/Event.h"
#include "performance/timeline/OnsetTimeline.h"
#include "performance/timeline/PitchTimeline.h"

namespace performer {

class TimelineManager {
private:
    inline static const unsigned int TIMELINE_SIZE = 100;

    unsigned int timelineSize;
    std::list<std::unique_ptr<const Event>> events;
    OnsetTimeline onsetTimeline;
    PitchTimeline pitchTimeline;

public:
    explicit TimelineManager();

    void addEvent(std::unique_ptr<const Event> event);

    const OnsetTimeline &getOnsetTimeline() const;

    const PitchTimeline &getPitchTimeline() const;

    int getTimelineSize() const;
};

}

#endif //PERFORMER_TIMELINEMANAGER_H
