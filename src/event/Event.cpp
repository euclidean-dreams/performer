#include "event/Event.h"

namespace performer {

Event::Event(std::unique_ptr<impresarioUtils::SerializedData> payload)
        : payload{move(payload)} {

}

ImpresarioSerialization::Identifier Event::getIdentifier() const {
    return payload->getIdentifier();
}

const ImpresarioSerialization::Onset *Event::getOnset() const {
    if (getIdentifier() == ImpresarioSerialization::Identifier::onset) {
        return ImpresarioSerialization::GetOnset(payload->getBuffer());
    } else {
        throw InvalidUnserializationException();
    }
}

const ImpresarioSerialization::Pitch *Event::getPitch() const {
    if (getIdentifier() == ImpresarioSerialization::Identifier::pitch) {
        return ImpresarioSerialization::GetPitch(payload->getBuffer());
    } else {
        throw InvalidUnserializationException();
    }
}

const ImpresarioSerialization::DisplaySignal *Event::getDisplaySignal() const {
    if (getIdentifier() == ImpresarioSerialization::Identifier::displaySignal) {
        return ImpresarioSerialization::GetDisplaySignal(payload->getBuffer());
    } else {
        throw InvalidUnserializationException();
    }
}

}
