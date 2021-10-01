#include "LedMatrixProxy.h"

namespace performer {

LedMatrixProxy::LedMatrixProxy(uint width, uint height)
        : matrix{height, {width, HSLColor{0, 0, 0}}} {

}

HSLColor LedMatrixProxy::getLed(Coordinate coordinate) {
    return matrix[coordinate.y][coordinate.x];
}

void LedMatrixProxy::setLed(Coordinate coordinate, HSLColor color) {
    matrix[coordinate.y][coordinate.x] = color;
}

bool LedMatrixProxy::isValid(Coordinate coordinate) {
    if (coordinate.x >= 0 && coordinate.x < width()) {
        if (coordinate.y >= 0 && coordinate.y < height()) {
            return true;
        }
    }
    return false;
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
