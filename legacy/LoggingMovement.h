#ifndef PERFORMER_LOGGINGMOVEMENT_H
#define PERFORMER_LOGGINGMOVEMENT_H

#include <spdlog/spdlog.h>
#include <ImpresarioUtils.h>
#include <ImpresarioSerialization.h>
#include "Config.h"
#include "performance/movement/Movement.h"

namespace performer {

class LoggingMovement : public Movement {
private:
    std::shared_ptr<spdlog::logger> logger;

public:
    LoggingMovement();

    void handleEvent(const Event &event) override;

    void conduct() override;
};

}

#endif //PERFORMER_LOGGINGMOVEMENT_H
