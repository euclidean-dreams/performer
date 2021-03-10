#ifndef PERFORMER_LEDMATRIXRENDERER_H
#define PERFORMER_LEDMATRIXRENDERER_H

#include <thread>
#include <chrono>
#include <zmq.hpp>
#include <NetworkSocket.h>
#include <Time.h>
#include <NonCopyable.h>
#include <LedPacket_generated.h>
#include "Config.h"
#include "ledMatrix/LedMatrix.h"

namespace performer {

class LedMatrixRenderer : impresarioUtils::NonCopyable {
private:
    std::unique_ptr<LedMatrix> ledMatrix;
    std::unique_ptr<impresarioUtils::NetworkSocket> inputSocket;

    std::unique_ptr<char[]> receiveLedPacketBuffer();

public:
    static void startRenderLoop(LedMatrixRenderer &ledMatrixRenderer);

    LedMatrixRenderer(std::unique_ptr<LedMatrix> ledMatrix,
                      std::unique_ptr<impresarioUtils::NetworkSocket> inputSocket);

    void render();

    bool finished();
};

}

#endif //PERFORMER_LEDMATRIXRENDERER_H
