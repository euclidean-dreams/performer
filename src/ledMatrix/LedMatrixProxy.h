#ifndef PERFORMER_LEDMATRIXPROXY_H
#define PERFORMER_LEDMATRIXPROXY_H

#include <vector>
#include "NonCopyable.h"
#include "color/HSLColor.h"
#include "color/RGBColor.h"

class LedMatrixProxy : NonCopyable {
private:
    vector<Color::RGBColor> matrix;

public:
    explicit LedMatrixProxy(uint ledCount);

    Color::RGBColor operator[](int index);

    void modifyLed(int index, Color::HSLColor color);

    void modifyLed(int index, Color::RGBColor color);

    int size() const;

};

#endif //PERFORMER_LEDMATRIXPROXY_H
