#ifndef PERFORMER_DRAGONCURVE_H
#define PERFORMER_DRAGONCURVE_H

#include "performance/action/ledMatrixAction/entity/lindogram/Lindogram.h"

namespace performer {

class DragonCurve : public Lindogram {
private:
    double scale;

protected:
    void applyRules(std::vector<char> &newState, char symbol) override;

    void processSymbol(char symbol) override;

public:
    DragonCurve(Coordinate origin, HSLColor rootColor, double orientation, int recursions, double scale);

};

}

#endif //PERFORMER_DRAGONCURVE_H
