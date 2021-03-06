#ifndef PERFORMER_TESTINGUTILS_H
#define PERFORMER_TESTINGUTILS_H

#include <spdlog/sinks/stdout_color_sinks.h>
#include "Config.h"

inline void disableLogger() {
    auto loggerName = static_cast<string>(LOGGER_NAME);
    if (!spdlog::get(loggerName)) {
        spdlog::stdout_color_mt(loggerName);
        spdlog::get(loggerName)->set_level(spdlog::level::off);
    }
}

#endif //PERFORMER_TESTINGUTILS_H
