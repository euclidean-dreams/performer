#include "LedMatrixProxy.h"

namespace performer {

LedMatrixProxy::LedMatrixProxy(uint ledCount)
        : matrix{ledCount, HSLColor{0, 0, 0}} {

}

HSLColor &LedMatrixProxy::operator[](int index) {
    return matrix[index];
}

const HSLColor &LedMatrixProxy::getLed(int index) const {
    return matrix[index];
}

int LedMatrixProxy::size() const {
    return matrix.size();
}

std::unique_ptr<std::lock_guard<std::mutex>> LedMatrixProxy::acquireLock() {
    return std::make_unique<std::lock_guard<std::mutex>>(mutex);
}

}
