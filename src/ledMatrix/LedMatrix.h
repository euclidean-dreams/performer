#ifndef PERFORMER_LEDMATRIX_H
#define PERFORMER_LEDMATRIX_H

#include <LedPacket_generated.h>
#include <NonCopyable.h>

namespace performer {

class LedMatrix : impresarioUtils::NonCopyable {
public:
    virtual ~LedMatrix() = default;

    virtual void render() = 0;

    virtual void consumeLedPacket(const ImpresarioSerialization::LedPacket *ledPacket) = 0;
};

}

#endif //PERFORMER_LEDMATRIX_H
