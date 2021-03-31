#ifndef PERFORMER_PERFORMANCE_H
#define PERFORMER_PERFORMANCE_H

#include <ImpresarioUtils.h>

namespace performer {

class Performance : impresarioUtils::NonCopyable {
public:
    virtual ~Performance() = default;

    virtual void perform() = 0;

    virtual bool finished() = 0;
};

}

#endif //PERFORMER_PERFORMANCE_H
