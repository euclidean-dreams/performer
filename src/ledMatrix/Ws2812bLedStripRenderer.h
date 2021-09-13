#ifndef PERFORMER_WS2812BLEDSTRIPRENDERER_H
#define PERFORMER_WS2812BLEDSTRIPRENDERER_H

#include <thread>
#include <chrono>
#include <ImpresarioUtils.h>
#include "Bootstrapper.h"
#include "Config.h"
#include "ledMatrix/Ws2812bLedStrip.h"
#include "ledMatrix/LedMatrixProxy.h"

namespace performer {

class Ws2812bLedStripRenderer : impresarioUtils::NonCopyable {
private:
    std::unique_ptr<Ws2812bLedStrip> ledStrip;
    std::shared_ptr<LedMatrixProxy> ledMatrixProxy;
    int refreshRate;

    void update();

public:
    static void startRenderLoop(std::unique_ptr<Ws2812bLedStripRenderer> ledMatrixRenderer);

    Ws2812bLedStripRenderer(std::unique_ptr<Ws2812bLedStrip> ledStrip, std::shared_ptr<LedMatrixProxy> ledMatrixProxy);

    void render();

    bool finished();
};

}

#endif //PERFORMER_WS2812BLEDSTRIPRENDERER_H
