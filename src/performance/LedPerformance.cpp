#include "LedPerformance.h"

LedPerformance::LedPerformance(context_t &context, const string &audioAttributeEndpoint)
        : tick{0},
          movements{},
          ledMatrix{18, 0, 60 * 4},
          randomNumberGenerator{},
          audioAttributeSocket{context, audioAttributeEndpoint, socket_type::sub, false},
          lastFlip{getCurrentTime()} {
    audioAttributeSocket.setSubscriptionFilter("");
    movements.emplace_back(make_unique<LoggingMovement>(ledMatrix));
    movements.emplace_back(make_unique<RippleMovement>(ledMatrix, randomNumberGenerator));
}

void LedPerformance::perform() {
    ledMatrix.clear();
    while (true) {
        auto startTime = getCurrentTime();
        unique_ptr<char[]> buffer;
        auto possibleNewerBuffer = audioAttributeSocket.receiveBuffer(recv_flags::dontwait);
        while (possibleNewerBuffer != nullptr) {
            buffer = move(possibleNewerBuffer);
            possibleNewerBuffer = audioAttributeSocket.receiveBuffer(recv_flags::dontwait);
        }
        const AudioAttributes *audioAttributes = nullptr;
        if (buffer != nullptr) {
            audioAttributes = GetAudioAttributes(buffer.get());
        }
        if (audioAttributes != nullptr) {
            auto onsetAggregate = audioAttributes->onsetAggregate();
            auto onsetsDetected = 0;
            for (int i = 0; i < onsetAggregate->methods()->size(); i++) {
                auto timestamp = (*onsetAggregate->timestamps())[i];
                if (timestamp > 0 && getCurrentTime() - timestamp < 10000) {
                    onsetsDetected++;
                }
            }
            if (onsetsDetected > 6 && getCurrentTime() - lastFlip > 3 * 1000 * 1000) {
                movements.pop_back();
                if (randomNumberGenerator.generate(5) == 0) {
                    movements.emplace_back(make_unique<BeatMovement>(ledMatrix, randomNumberGenerator));
                } else {
                    movements.emplace_back(make_unique<RippleMovement>(ledMatrix, randomNumberGenerator));
                }
                lastFlip = getCurrentTime();
            }
        }
        for (auto &movement: movements) {
            movement->present(tick, audioAttributes);
        }

        auto performanceTime = getCurrentTime() - startTime;
        if (MIN_TIME_BETWEEN_RENDER_CALLS > performanceTime) {
            sleep_for(microseconds(MIN_TIME_BETWEEN_RENDER_CALLS - performanceTime));
        }
        ledMatrix.render();
        tick++;
        auto cycleTime = getCurrentTime() - startTime;
        if (TICK_INTERVAL_MICROSECONDS > cycleTime) {
            sleep_for(microseconds(TICK_INTERVAL_MICROSECONDS - cycleTime));
        }
    }
}
