#ifndef PERFORMER_PITCHTIMELINE_H
#define PERFORMER_PITCHTIMELINE_H

#include <list>
#include <ImpresarioSerialization.h>
#include "performance/timeline/Timeline.h"

namespace performer {

class PitchTimeline : public Timeline {
protected:
    unsigned int maxSize;
    std::list<std::unique_ptr<const Event>> events;
    std::list<const ImpresarioSerialization::Pitch *> timeline;

public:
    explicit PitchTimeline(unsigned int maxSize);

    void addEvent(std::unique_ptr<const Event> event) override;

    std::list<const ImpresarioSerialization::Pitch *>::const_iterator begin() const;

    std::list<const ImpresarioSerialization::Pitch *>::const_iterator end() const;
};

}

#endif //PERFORMER_PITCHTIMELINE_H
