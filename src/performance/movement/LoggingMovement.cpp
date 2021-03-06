#include "LoggingMovement.h"

LoggingMovement::LoggingMovement(LedMatrix &ledMatrix)
        : ledMatrix{ledMatrix},
          logger{spdlog::get(static_cast<string>(LOGGER_NAME))} {}

void LoggingMovement::present(uint32_t tick, const AudioAttributes *audioAttributes) {
    if (audioAttributes != nullptr) {
        auto onsetAggregate = audioAttributes->onsetAggregate();
        logger->info("got onset:");
        for (int i = 0; i < onsetAggregate->methods()->size(); i++) {
            auto method = (*onsetAggregate->methods())[i];
            auto timestamp = (*onsetAggregate->timestamps())[i];
            if (timestamp > 0) {
                auto latency = getCurrentTime() - timestamp;
                logger->info("method: {}, latency: {}", method, latency);
            }
        }
        logger->info("");
    }
}