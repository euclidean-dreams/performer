#include "LedMatrixProxy.h"

namespace performer {

LedMatrixProxy::LedMatrixProxy(uint width, uint height)
        : matrix{height, {width, HSLColor{0, 0, 0}}} {

}

HSLColor LedMatrixProxy::getLed(int x, int y) {
    return matrix[y][x];
}

void LedMatrixProxy::setLed(int x, int y, HSLColor color) {
    matrix[y][x] = color;
}

void LedMatrixProxy::clear() {
    for (int y = 0; y < height(); y++) {
        for (int x = 0; x < width(); x++) {
            matrix[y][x] = HSLColor{0, 0, 0};
        }
    }
}

int LedMatrixProxy::width() const {
    return static_cast<int>(matrix[0].size());
}

int LedMatrixProxy::height() const {
    return static_cast<int>(matrix.size());
}

int LedMatrixProxy::size() const {
    return width() * height();
}

std::unique_ptr<std::lock_guard<std::mutex>> LedMatrixProxy::acquireLock() {
    return std::make_unique<std::lock_guard<std::mutex>>(mutex);
}

int LedMatrixProxy::getBrightness() {
    return brightness;
}

void LedMatrixProxy::setBrightness(int newBrightness) {
    brightness = newBrightness;
}

}
