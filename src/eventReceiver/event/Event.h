#ifndef PERFORMER_EVENT_H
#define PERFORMER_EVENT_H

#include <NonCopyable.h>

namespace performer {

class Event : impresarioUtils::NonCopyable {
public:
    virtual ~Event() = default;
};

}

#endif //PERFORMER_EVENT_H
