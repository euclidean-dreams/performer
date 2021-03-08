#ifndef PERFORMER_LEDPERFORMANCE_H
#define PERFORMER_LEDPERFORMANCE_H

#include <random>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include <zmq.hpp>
#include "Utils.h"
#include "NetworkSocket.h"
#include "RandomNumberGenerator.h"
#include "AudioAttributes_generated.h"
#include "ledMatrix/Ws2812bLedMatrix.h"
#include "Performance.h"
#include "performance/movement/LoggingMovement.h"
#include "performance/movement/RippleMovement.h"
#include "performance/movement/BeatMovement.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;
using namespace zmq;
using namespace ImpresarioSerialization;

class LedPerformance : public Performance {
private:
    uint32_t tick;
    vector<std::unique_ptr<Movement>> eventReceivers;
    vector<std::unique_ptr<Movement>> movements;
    Ws2812bLedMatrix ledMatrix;
    RandomNumberGenerator randomNumberGenerator;
    NetworkSocket audioAttributeSocket;
    uint64_t lastFlip;

public:
    explicit LedPerformance(context_t &context, const string &audioAttributeEndpoint);

    void perform() override;


};

#endif //PERFORMER_LEDPERFORMANCE_H
