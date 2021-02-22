#ifndef PERFORMER_TESTINGUTILS_H
#define PERFORMER_TESTINGUTILS_H

#include <spdlog/sinks/stdout_color_sinks.h>
#include "Config.h"

inline void disableLogger() {
    if (!spdlog::get(LOGGER_NAME)) {
        spdlog::stdout_color_mt(LOGGER_NAME);
        spdlog::get(LOGGER_NAME)->set_level(spdlog::level::off);
    }
}

#endif //PERFORMER_TESTINGUTILS_H
