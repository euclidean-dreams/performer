#include "LoggingMovement.h"

namespace performer {

LoggingMovement::LoggingMovement()
        : logger{spdlog::get(static_cast<std::string>(LOGGER_NAME))} {

}

void LoggingMovement::handleEvent(const Event &event) {
    if (dynamic_cast<const OnsetEvent *>(&event) != nullptr) {
        auto &onsetEvent = dynamic_cast<const OnsetEvent &>(event);
        auto methodName = ImpresarioSerialization::EnumNameOnsetMethod(onsetEvent.getMethod());
        auto elapsedTime = impresarioUtils::getElapsedTime(onsetEvent.getTimestamp());
        auto latency = impresarioUtils::getElapsedTime(onsetEvent.getSampleTimestamp());
        logger->info("onset received, method: {}, time since onset: {}, latency: {}", methodName, elapsedTime, latency);
    }
}

void LoggingMovement::conduct() {

}

}
