#include "ActionCollection.h"

namespace performer {

ActionCollection::ActionCollection()
        : actions{} {

}

void ActionCollection::addAction(std::unique_ptr<Action> action) {
    actions.push_back(move(action));
}

void ActionCollection::trimActions(int maxActions) {
    while (actions.size() > maxActions) {
        actions.pop_front();
    }
}

void ActionCollection::clear() {
    actions.clear();
}

void ActionCollection::executeActions() {
    auto iterator = actions.begin();
    while (iterator != actions.end()) {
        if ((*iterator)->finished()) {
            iterator = actions.erase(iterator);
        } else {
            (*iterator)->execute();
            iterator++;
        }
    }
}

unsigned int ActionCollection::size() {
    return actions.size();
}

}
