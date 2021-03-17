#ifndef PERFORMER_EVENT_H
#define PERFORMER_EVENT_H

#include <memory>
#include <SerializedData.h>
#include <NonCopyable.h>
#include <Onset_generated.h>
#include <Pitch_generated.h>
#include "eventReceiver/InvalidUnserializationException.h"

namespace performer {

class Event : impresarioUtils::NonCopyable {
private:
    std::unique_ptr<impresarioUtils::SerializedData> payload;

public:
    explicit Event(std::unique_ptr<impresarioUtils::SerializedData> payload);

    ImpresarioSerialization::Identifier getIdentifier() const;

    const ImpresarioSerialization::Onset *getOnset() const;

    const ImpresarioSerialization::Pitch *getPitch() const;
};

}

#endif //PERFORMER_EVENT_H
