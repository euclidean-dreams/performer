#ifndef PERFORMER_LEDMATRIXRENDERER_H
#define PERFORMER_LEDMATRIXRENDERER_H

#include <thread>
#include <chrono>
#include <ImpresarioUtils.h>
#include "ledMatrix/LedMatrix.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class LedMatrixRenderer : impresarioUtils::NonCopyable {
private:
    inline static const int TICK_INTERVAL_MICROSECONDS = 2500;
    std::unique_ptr<LedMatrix> ledMatrix;
    std::shared_ptr<LedMatrixProxy> ledMatrixProxy;

public:
    static void startRenderLoop(std::unique_ptr<LedMatrixRenderer> ledMatrixRenderer);

    LedMatrixRenderer(std::unique_ptr<LedMatrix> ledMatrix, std::shared_ptr<LedMatrixProxy> ledMatrixProxy);

    void render();

    bool finished();
};

}

#endif //PERFORMER_LEDMATRIXRENDERER_H
