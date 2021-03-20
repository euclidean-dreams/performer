#ifndef PERFORMER_ONSETTIMELINE_H
#define PERFORMER_ONSETTIMELINE_H

#include <list>
#include <IdentifierWrapper_generated.h>
#include "performance/timeline/Timeline.h"

namespace performer {

class OnsetTimeline : public Timeline {
protected:
    unsigned int maxSize;
    std::list<std::unique_ptr<const Event>> events;
    std::list<const ImpresarioSerialization::Onset *> timeline;

public:
    explicit OnsetTimeline(unsigned int maxSize);

    void addEvent(std::unique_ptr<const Event> event) override;

    std::list<const ImpresarioSerialization::Onset *>::const_iterator begin() const;

    std::list<const ImpresarioSerialization::Onset *>::const_iterator end() const;
};

}

#endif //PERFORMER_ONSETTIMELINE_H
