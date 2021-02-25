#ifndef PERFORMER_LOGGINGMOVEMENT_H
#define PERFORMER_LOGGINGMOVEMENT_H

#include "Utils.h"
#include "AudioAttributes_generated.h"
#include "ledMatrix/LedMatrix.h"
#include "Movement.h"

class LoggingMovement : public Movement {
private:
    LedMatrix &ledMatrix;
    shared_ptr<spdlog::logger> logger;

public:
    explicit LoggingMovement(LedMatrix &ledMatrix);

    void present(uint32_t tick, const AudioAttributes *audioAttributes) override;
};

#endif //PERFORMER_LOGGINGMOVEMENT_H
