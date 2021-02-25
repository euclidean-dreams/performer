#ifndef PERFORMER_CONFIG_H
#define PERFORMER_CONFIG_H

#include <string>

using namespace std;

// logger
const static string LOGGER_NAME = "performer";

// led performance
const static int LED_MATRIX_INITIAL_BRIGHTNESS = 50;
const static int MIN_TIME_BETWEEN_RENDER_CALLS = 1000;
const static int TICK_INTERVAL_MICROSECONDS = 3000;

// network
const static string CONDUCTOR_ENDPOINT = "tcp://10.0.0.181:44441";

#endif //PERFORMER_CONFIG_H
