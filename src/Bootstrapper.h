#ifndef PERFORMER_BOOTSTRAPPER_H
#define PERFORMER_BOOTSTRAPPER_H

#include <thread>
#include <zmq.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <NetworkSocket.h>
#include "Config.h"
#include "performance/LedPerformance.h"
#include "ledMatrix/LedMatrixRenderer.h"
#include "ledMatrix/Ws2812bLedMatrix.h"

namespace performer {

class Bootstrapper {
public:
    static void boot();
};

}

#endif //PERFORMER_BOOTSTRAPPER_H
