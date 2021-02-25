#include <zmq.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "Config.h"
#include "performance/LedPerformance.h"

using namespace zmq;

int main() {
    spdlog::stdout_color_mt(LOGGER_NAME);
    context_t context(1);
    auto ledPerformance = make_unique<LedPerformance>(context, CONDUCTOR_ENDPOINT);
    ledPerformance->perform();
}
