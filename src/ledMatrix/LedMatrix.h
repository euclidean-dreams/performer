#ifndef PERFORMER_LEDMATRIX_H
#define PERFORMER_LEDMATRIX_H

#include <ImpresarioUtils.h>
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class LedMatrix : impresarioUtils::NonCopyable {
public:
    virtual ~LedMatrix() = default;

    virtual void render() = 0;

    virtual void update(LedMatrixProxy &proxy) = 0;
};

}

#endif //PERFORMER_LEDMATRIX_H
