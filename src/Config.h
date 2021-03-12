#ifndef PERFORMER_CONFIG_H
#define PERFORMER_CONFIG_H

#include <iostream>
#include <string_view>

namespace performer {

// logger
constexpr std::string_view LOGGER_NAME = "performer";

// led performance
constexpr int LED_COUNT = 60 * 3;
constexpr int LED_MATRIX_INITIAL_BRIGHTNESS = 50;
constexpr int TICK_INTERVAL_MICROSECONDS = 2500;
constexpr int PERFORMANCE_WAKE_INTERVAL = 100;

// network
constexpr std::string_view CONDUCTOR_ENDPOINT = "tcp://10.0.0.181:44441";
constexpr std::string_view ONSET_SUBSCRIPTION_FILTER = "";

}

#endif //PERFORMER_CONFIG_H
