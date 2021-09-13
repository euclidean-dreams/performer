#ifndef PERFORMER_CONFIG_H
#define PERFORMER_CONFIG_H

#include <memory>
#include <stdexcept>
#include <yaml-cpp/yaml.h>

namespace performer {

class Config {
private:
    static constexpr std::string_view CONFIG_FILE_PATH = "../config.yml";
    static std::unique_ptr<Config> instance;

    // general
    std::string loggerName;
    std::string conductorEndpoint;
    std::string fasciaEndpoint;

    // led strip
    int ledMatrixWidth;
    int ledMatrixHeight;

    // ws2812b
    int gpioNumber;
    int pwmChannel;
    int initialBrightness;
    int refreshRate;

    Config();

public:
    static Config &getInstance();

    static void initialize();

    // general
    std::string getLoggerName() const { return loggerName; }

    std::string getConductorEndpoint() const { return conductorEndpoint; }

    std::string getFasciaEndpoint() const { return fasciaEndpoint; }

    // led strip
    int getLedMatrixWidth() { return ledMatrixWidth; }

    int getledMatrixHeight() { return ledMatrixHeight; }

    // ws2812b
    int getGpioNumber() { return gpioNumber; }

    int getPwmChannel() { return pwmChannel; }

    int getInitialBrightness() { return initialBrightness; }

    int getRefreshRate() { return refreshRate; }
};

}

#endif //PERFORMER_CONFIG_H
