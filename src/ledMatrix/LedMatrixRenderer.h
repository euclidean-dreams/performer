#ifndef PERFORMER_LEDMATRIXRENDERER_H
#define PERFORMER_LEDMATRIXRENDERER_H

#include <thread>
#include "Utils.h"
#include "NetworkSocket.h"
#include "LedPacket_generated.h"
#include "Config.h"
#include "LedMatrix.h"

using namespace ImpresarioSerialization;

class LedMatrixRenderer {
private:
    std::unique_ptr<LedMatrix> ledMatrix;
    std::unique_ptr<NetworkSocket> inputSocket;

    std::unique_ptr<char[]> receiveLedPacketBuffer();

public:
    LedMatrixRenderer(std::unique_ptr<LedMatrix> ledMatrix, std::unique_ptr<NetworkSocket> inputSocket);

    void render();

    bool finished();

    static void startRenderLoop(LedMatrixRenderer &ledMatrixRenderer);
};

#endif //PERFORMER_LEDMATRIXRENDERER_H
