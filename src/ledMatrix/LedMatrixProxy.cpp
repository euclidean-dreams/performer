#include "LedMatrixProxy.h"

namespace performer {

LedMatrixProxy::LedMatrixProxy(uint ledCount)
        : matrix{ledCount, HSLColor{0, 0, 0}} {

}

HSLColor &LedMatrixProxy::operator[](int index) {
    if (index < 0 || index >= matrix.size()) {
        std::ostringstream errorMessage;
        errorMessage << "attempted to modify an led at an invalid index: " << index;
        throw std::out_of_range(errorMessage.str());
    }
    return matrix[index];
}

int LedMatrixProxy::size() const {
    return matrix.size();
}

std::unique_ptr<flatbuffers::FlatBufferBuilder> LedMatrixProxy::generateLedPacket() const {
    auto builder = std::make_unique<flatbuffers::FlatBufferBuilder>();
    std::vector<ImpresarioSerialization::RGBColor> leds;
    for (auto &color : matrix) {
        leds.push_back(color.convertToRGB());
    }
    auto serializedLeds = builder->CreateVectorOfStructs(leds);
    auto ledPacket = ImpresarioSerialization::CreateLedPacket(*builder, serializedLeds);
    builder->Finish(ledPacket);
    return builder;
}

}
