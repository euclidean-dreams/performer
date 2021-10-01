#ifndef PERFORMER_LEDMATRIXPROXY_H
#define PERFORMER_LEDMATRIXPROXY_H

#include <mutex>
#include <condition_variable>
#include <vector>
#include <sstream>
#include <ImpresarioUtils.h>
#include "Coordinate.h"
#include "color/HSLColor.h"

namespace performer {

class LedMatrixProxy : impresarioUtils::NonCopyable {
private:
    std::mutex mutex;
    std::vector<std::vector<HSLColor>> matrix;
    int brightness;

public:
    explicit LedMatrixProxy(uint width, uint height);

    HSLColor getLed(Coordinate coordinate);

    void setLed(Coordinate coordinate, HSLColor color);

    bool isValid(Coordinate coordinate);

    int getBrightness();

    void setBrightness(int newBrightness);

    void clear();

    int width() const;

    int height() const;

    int size() const;

    std::unique_ptr<std::lock_guard<std::mutex>> acquireLock();
};

}

#endif //PERFORMER_LEDMATRIXPROXY_H
