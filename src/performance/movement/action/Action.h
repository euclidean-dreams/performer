#ifndef PERFORMER_ACTION_H
#define PERFORMER_ACTION_H

#include "Utils.h"
#include "NonCopyable.h"

class Action : NonCopyable {
protected:
    uint64_t initialTimestamp;

public:
    explicit Action() : initialTimestamp{getCurrentTime()} {}

    virtual ~Action() = default;

    virtual void execute() = 0;

    virtual bool finished() = 0;
};

#endif //PERFORMER_ACTION_H
