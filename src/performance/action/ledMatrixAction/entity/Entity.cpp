
#include "Entity.h"

namespace performer {

Entity::Entity(Coordinate origin, HSLColor rootColor)
        : origin{origin},
          rootColor{rootColor} {
}

HSLColor Entity::getRootColor() {
    return rootColor;
}

void Entity::setRootColor(HSLColor color) {
    rootColor = color;
}

}
