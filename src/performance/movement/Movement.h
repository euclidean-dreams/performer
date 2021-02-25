#ifndef PERFORMER_MOVEMENT_H
#define PERFORMER_MOVEMENT_H

#include <cstdint>
#include "NonCopyable.h"

using namespace ImpresarioSerialization;

class Movement : NonCopyable {
public:
    virtual ~Movement() = default;

    virtual void present(uint32_t tick, const AudioAttributes *audioAttributes) = 0;
};

#endif //PERFORMER_MOVEMENT_H
