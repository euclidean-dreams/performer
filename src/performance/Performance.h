#ifndef PERFORMER_PERFORMANCE_H
#define PERFORMER_PERFORMANCE_H

#include "NonCopyable.h"

class Performance : NonCopyable {
public:
    virtual ~Performance() = default;

    virtual void perform() = 0;
};

#endif //PERFORMER_PERFORMANCE_H
