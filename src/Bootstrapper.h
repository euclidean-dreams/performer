#ifndef PERFORMER_BOOTSTRAPPER_H
#define PERFORMER_BOOTSTRAPPER_H

#include <string_view>
#include <vector>
#include <thread>
#include <zmq.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <ImpresarioUtils.h>
#include "performance/LedPerformance.h"
#include "ledMatrix/Ws2812bLedStripRenderer.h"
#include "ledMatrix/Ws2812bLedStrip.h"

namespace performer {

class Bootstrapper {
public:
    static void boot();
};

}

#endif //PERFORMER_BOOTSTRAPPER_H
