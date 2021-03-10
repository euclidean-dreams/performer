#ifndef PERFORMER_ONSETEVENT_H
#define PERFORMER_ONSETEVENT_H

#include <Onset_generated.h>
#include "eventReceiver/event/Event.h"

namespace performer {

class OnsetEvent : public Event {
private:
    std::unique_ptr<char[]> buffer;
    const ImpresarioSerialization::Onset *serializedOnset;

public:
    explicit OnsetEvent(std::unique_ptr<char[]> buffer);

    uint64_t getTimestamp();

    ImpresarioSerialization::OnsetMethod getMethod();

};

}

#endif //PERFORMER_ONSETEVENT_H
