#ifndef PERFORMER_LEDMATRIXPROXY_H
#define PERFORMER_LEDMATRIXPROXY_H

#include <mutex>
#include <condition_variable>
#include <vector>
#include <sstream>
#include <ImpresarioUtils.h>
#include "color/HSLColor.h"

namespace performer {

class LedMatrixProxy : impresarioUtils::NonCopyable {
private:
    std::mutex mutex;
    std::vector<std::vector<HSLColor>> matrix;

public:
    explicit LedMatrixProxy(uint width, uint height);

    HSLColor getLed(int x, int y);

    void setLed(int x, int y, HSLColor color);

    void clear();

    int width() const;

    int height() const;

    int size() const;

    std::unique_ptr<std::lock_guard<std::mutex>> acquireLock();
};

}

#endif //PERFORMER_LEDMATRIXPROXY_H
