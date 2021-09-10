#ifndef PERFORMER_EVENT_H
#define PERFORMER_EVENT_H

#include <memory>
#include <ImpresarioUtils.h>
#include <ImpresarioSerialization.h>
#include "event/InvalidUnserializationException.h"

namespace performer {

class Event : impresarioUtils::NonCopyable {
private:
    std::unique_ptr<impresarioUtils::SerializedData> payload;

public:
    explicit Event(std::unique_ptr<impresarioUtils::SerializedData> payload);

    ImpresarioSerialization::Identifier getIdentifier() const;

    const ImpresarioSerialization::Onset *getOnset() const;

    const ImpresarioSerialization::Pitch *getPitch() const;

    const ImpresarioSerialization::DisplaySignal *getDisplaySignal() const;
};

}

#endif //PERFORMER_EVENT_H
