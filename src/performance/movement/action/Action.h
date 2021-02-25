#ifndef PERFORMER_ACTION_H
#define PERFORMER_ACTION_H

#include <cstdint>
#include "NonCopyable.h"

class Action : NonCopyable {
protected:
    uint32_t initialTick;

public:
    explicit Action(uint32_t initialTick) : initialTick{initialTick} {}

    virtual ~Action() = default;

    virtual void execute(uint32_t tick) = 0;

    virtual bool finished() = 0;
};

#endif //PERFORMER_ACTION_H
