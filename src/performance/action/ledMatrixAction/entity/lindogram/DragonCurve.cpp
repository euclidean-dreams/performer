#include "DragonCurve.h"

namespace performer {

DragonCurve::DragonCurve(Coordinate origin, HSLColor rootColor, double orientation, int recursions, double scale)
        : Lindogram(origin, rootColor, orientation),
          scale{scale} {
    state.push_back(0);
    for (int i = 0; i < recursions; i++) {
        recurse();
    }
}

void DragonCurve::applyRules(std::vector<char> &newState, char symbol) {
    if (symbol == 0) {
        newState.push_back(0);
        newState.push_back(7);
        newState.push_back(1);
    } else if (symbol == 1) {
        newState.push_back(0);
        newState.push_back(8);
        newState.push_back(1);
    } else {
        newState.push_back(symbol);
    }
}

void DragonCurve::processSymbol(char symbol) {
    if (symbol == 0 || symbol == 1) {
        advance(scale);
    } else if (symbol == 7) {
        rotate(M_PI / 2);
    } else if (symbol == 8) {
        rotate(-M_PI / 2);
    }
}

}
