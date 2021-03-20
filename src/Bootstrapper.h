#ifndef PERFORMER_BOOTSTRAPPER_H
#define PERFORMER_BOOTSTRAPPER_H

#include <string_view>
#include <vector>
#include <thread>
#include <zmq.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <NetworkSocket.h>
#include "performance/LedPerformance.h"
#include "ledMatrix/LedMatrixRenderer.h"
#include "ledMatrix/Ws2812bLedMatrix.h"
#include "event/EventReceiver.h"

namespace performer {


class Bootstrapper {
private:
    inline static const int LED_COUNT = 60 * 3;
    inline static const std::string_view CONDUCTOR_ENDPOINT = "tcp://10.0.0.181:44441";

public:
    static void boot();
};

}

#endif //PERFORMER_BOOTSTRAPPER_H
