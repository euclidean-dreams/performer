#ifndef PERFORMER_ONSETEVENT_H
#define PERFORMER_ONSETEVENT_H

#include "Event.h"
#include "Onset_generated.h"

using namespace ImpresarioSerialization;

class OnsetEvent : public Event {
private:
    std::unique_ptr<char[]> buffer;
    const Onset *onset;

public:
    explicit OnsetEvent(std::unique_ptr<char[]> buffer);

    uint64_t getTimestamp();

    OnsetMethod getMethod();

};

#endif //PERFORMER_ONSETEVENT_H
