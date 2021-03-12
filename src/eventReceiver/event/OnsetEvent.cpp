#include "OnsetEvent.h"

namespace performer {

OnsetEvent::OnsetEvent(std::unique_ptr<char[]> buffer)
        : buffer{move(buffer)},
          serializedOnset{ImpresarioSerialization::GetOnset(this->buffer.get())} {

}

uint64_t OnsetEvent::getTimestamp() const {
    return serializedOnset->timestamp();
}

ImpresarioSerialization::OnsetMethod OnsetEvent::getMethod() const {
    return serializedOnset->method();
}

uint64_t OnsetEvent::getSampleTimestamp() const {
    return serializedOnset->sampleTimestamp();
}

}
