#include "Config.h"

namespace performer {

std::unique_ptr<Config> Config::instance = nullptr;

void Config::initialize() {
    if (instance == nullptr) {
        instance = std::unique_ptr<Config>(new Config());
    } else {
        throw std::logic_error("Attempted to initialize Config singleton more than once");
    }
}

Config &Config::getInstance() {
    return *instance;
}

Config::Config() {
    auto configFile = YAML::LoadFile(std::string{CONFIG_FILE_PATH});

    // general
    loggerName = configFile["general"]["loggerName"].as<std::string>();
    conductorEndpoint = configFile["general"]["conductorEndpoint"].as<std::string>();
    fasciaEndpoint = configFile["general"]["fasciaEndpoint"].as<std::string>();

    // led matrix
    ledMatrixWidth = configFile["ledMatrix"]["width"].as<int>();
    ledMatrixHeight = configFile["ledMatrix"]["height"].as<int>();

    // ws2812b
    pwmChannel = configFile["ws2812b"]["pwmChannel"].as<int>();
    dmaChannel = configFile["ws2812b"]["dmaChannel"].as<int>();
    initialBrightness = configFile["ws2812b"]["initialBrightness"].as<int>();
    maxBrightness = configFile["ws2812b"]["maxBrightness"].as<int>();
    refreshRate = configFile["ws2812b"]["refreshRate"].as<int>();
}

}
