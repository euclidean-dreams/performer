#ifndef PERFORMER_MOVEMENT_H
#define PERFORMER_MOVEMENT_H

#include <ImpresarioUtils.h>

namespace performer {

class Movement : impresarioUtils::NonCopyable {
public:
    virtual ~Movement() = default;

    virtual void handleIncomingPacket(const impresarioUtils::Packet &packet) = 0;

    virtual void conduct() = 0;
};

}

#endif //PERFORMER_MOVEMENT_H
