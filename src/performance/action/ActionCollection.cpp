#include "ActionCollection.h"

namespace performer {

ActionCollection::ActionCollection()
        : actions{} {

}

void ActionCollection::addAction(std::unique_ptr<Action> action) {
    actions.push_back(move(action));
}

void ActionCollection::executeActions() {
    auto iterator = actions.begin();
    while (iterator != actions.end()) {
        if ((*iterator)->finished()) {
            (*iterator)->cleanup();
            iterator = actions.erase(iterator);
        } else {
            (*iterator)->execute();
            iterator++;
        }
    }
}

}
