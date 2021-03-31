#ifndef PERFORMER_ACTION_H
#define PERFORMER_ACTION_H

#include <ImpresarioUtils.h>

namespace performer {

class Action : impresarioUtils::NonCopyable {
public:
    virtual ~Action() = default;

    virtual void execute() = 0;

    virtual bool finished() = 0;

    virtual void cleanup() = 0;
};

}

#endif //PERFORMER_ACTION_H
