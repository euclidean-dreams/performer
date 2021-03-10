#ifndef PERFORMER_LEDMATRIXPROXY_H
#define PERFORMER_LEDMATRIXPROXY_H

#include <vector>
#include <sstream>
#include <NonCopyable.h>
#include <LedPacket_generated.h>
#include "color/HSLColor.h"

namespace performer {

class LedMatrixProxy : impresarioUtils::NonCopyable {
private:
    std::vector<HSLColor> matrix;

public:
    explicit LedMatrixProxy(uint ledCount);

    HSLColor &operator[](int index);

    int size() const;

    std::unique_ptr<flatbuffers::FlatBufferBuilder> generateLedPacket() const;
};

}

#endif //PERFORMER_LEDMATRIXPROXY_H
