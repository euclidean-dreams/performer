#ifndef PERFORMER_ACTION_H
#define PERFORMER_ACTION_H

#include <Time.h>
#include <NonCopyable.h>

namespace performer {

class Action : impresarioUtils::NonCopyable {
protected:
    uint64_t initialTimestamp;

public:
    explicit Action() : initialTimestamp{impresarioUtils::getCurrentTime()} {}

    virtual ~Action() = default;

    virtual void execute() = 0;

    virtual bool finished() = 0;
};

}

#endif //PERFORMER_ACTION_H
