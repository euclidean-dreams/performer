#ifndef PERFORMER_CONFIG_H
#define PERFORMER_CONFIG_H

#include <iostream>
#include <string_view>

using namespace std;

// logger
constexpr string_view LOGGER_NAME = "performer";

// led performance
constexpr int LED_MATRIX_INITIAL_BRIGHTNESS = 50;
constexpr int MIN_TIME_BETWEEN_RENDER_CALLS = 2000;
constexpr int TICK_INTERVAL_MICROSECONDS = 3000;

// network
constexpr string_view CONDUCTOR_ENDPOINT = "tcp://10.0.0.181:44441";

#endif //PERFORMER_CONFIG_H
