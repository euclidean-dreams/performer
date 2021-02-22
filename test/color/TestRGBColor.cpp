#include <gtest/gtest.h>
#include "TestingUtils.h"
#include "color/RGBColor.h"

using namespace testing;

class RGBColorTest : public Test {
protected:
    void SetUp() override {
        disableLogger();
    }
};

TEST_F(RGBColorTest, Construction) {
    RGBColor{0, 0, 0};
}