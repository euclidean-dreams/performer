#include <spdlog/sinks/stdout_color_sinks.h>
#include "Config.h"

int main() {
    spdlog::stdout_color_mt(LOGGER_NAME);
}
