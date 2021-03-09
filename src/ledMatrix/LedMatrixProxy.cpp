#include "LedMatrixProxy.h"

LedMatrixProxy::LedMatrixProxy(uint ledCount)
        : matrix{ledCount, Color::RGBColor{0, 0, 0}} {

}

Color::RGBColor LedMatrixProxy::operator[](int index) {
    return matrix[index];
}

void LedMatrixProxy::modifyLed(int index, Color::HSLColor color) {
    modifyLed(index, color.convertToRGB());
}

void LedMatrixProxy::modifyLed(int index, Color::RGBColor color) {
    if (index < 0 || index >= matrix.size()) {
        spdlog::get(static_cast<string>(LOGGER_NAME))->error(
                "attempted to modify an led at an invalid index: {}", index
        );
        throw out_of_range("attempted to modify an led at an invalid index");
    } else {
        matrix[index] = color;
    }
}

int LedMatrixProxy::size() const {
    return matrix.size();
}
