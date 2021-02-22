#ifndef PERFORMER_LEDMATRIX_H
#define PERFORMER_LEDMATRIX_H

#include "NonCopyable.h"

class LedMatrix : NonCopyable {
public:
    virtual ~LedMatrix() = default;

    virtual void render() = 0;

    virtual void clear() = 0;

    virtual void modifyLed(int index, HSLColor color) = 0;

    virtual void modifyLed(int index, RGBColor color) = 0;

    virtual int getLedCount() const = 0;
};

#endif //PERFORMER_LEDMATRIX_H
