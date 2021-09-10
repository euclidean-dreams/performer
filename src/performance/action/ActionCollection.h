#ifndef PERFORMER_ACTIONCOLLECTION_H
#define PERFORMER_ACTIONCOLLECTION_H

#include <memory>
#include <list>
#include "Action.h"

namespace performer {

class ActionCollection {
private:
    std::list<std::unique_ptr<Action>> actions;

public:
    ActionCollection();

    void addAction(std::unique_ptr<Action> action);

    void trimActions(int maxActions);

    void executeActions();

    unsigned int size();
};

}

#endif //PERFORMER_ACTIONCOLLECTION_H
