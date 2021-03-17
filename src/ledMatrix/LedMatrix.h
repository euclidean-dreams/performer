#ifndef PERFORMER_LEDMATRIX_H
#define PERFORMER_LEDMATRIX_H

#include "ledMatrix/LedMatrixProxy.h"
#include <NonCopyable.h>

namespace performer {

class LedMatrix : impresarioUtils::NonCopyable {
public:
    virtual ~LedMatrix() = default;

    virtual void render() = 0;

    virtual void update(LedMatrixProxy &proxy) = 0;
};

}

#endif //PERFORMER_LEDMATRIX_H
