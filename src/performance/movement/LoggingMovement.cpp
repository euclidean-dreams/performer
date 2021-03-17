#include "LoggingMovement.h"

namespace performer {

LoggingMovement::LoggingMovement()
        : logger{spdlog::get(static_cast<std::string>(LOGGER_NAME))} {

}

void LoggingMovement::handleEvent(const Event &event) {
    if (event.getIdentifier() == ImpresarioSerialization::Identifier::onset) {
        auto onset = event.getOnset();
        auto methodName = ImpresarioSerialization::EnumNameOnsetMethod(onset->method());
        auto elapsedTime = impresarioUtils::getElapsedTime(onset->timestamp());
        auto latency = impresarioUtils::getElapsedTime(onset->sampleTimestamp());
        logger->info("onset received, method: {}, time since onset: {}, latency: {}", methodName, elapsedTime, latency);
    } else if (event.getIdentifier() == ImpresarioSerialization::Identifier::pitch) {
        auto pitch = event.getPitch();
        auto methodName = ImpresarioSerialization::EnumNamePitchMethod(pitch->method());
        auto latency = impresarioUtils::getElapsedTime(pitch->sampleTimestamp());
        logger->info("pitch received, method: {}, pitch: {}, confidence: {}, latency: {}",
                     methodName, pitch->pitch(), pitch->confidence(), latency);
    }
}

void LoggingMovement::conduct() {

}

}
