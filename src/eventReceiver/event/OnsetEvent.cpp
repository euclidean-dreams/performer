#include "OnsetEvent.h"

OnsetEvent::OnsetEvent(std::unique_ptr<char[]> buffer)
        : buffer{move(buffer)},
          onset{GetOnset(this->buffer.get())} {

}

uint64_t OnsetEvent::getTimestamp() {
    return onset->timestamp();
}

OnsetMethod OnsetEvent::getMethod() {
    return onset->method();
}

