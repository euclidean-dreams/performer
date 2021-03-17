#ifndef PERFORMER_LEDMATRIXPROXY_H
#define PERFORMER_LEDMATRIXPROXY_H

#include <mutex>
#include <condition_variable>
#include <vector>
#include <sstream>
#include <NonCopyable.h>
#include "color/HSLColor.h"

namespace performer {

class LedMatrixProxy : impresarioUtils::NonCopyable {
private:
    std::mutex mutex;
    std::vector<HSLColor> matrix;

public:
    explicit LedMatrixProxy(uint ledCount);

    HSLColor &operator[](int index);

    const HSLColor &getLed(int index) const;

    int size() const;

    std::unique_ptr<std::lock_guard<std::mutex>> acquireLock();
};

}

#endif //PERFORMER_LEDMATRIXPROXY_H
