#include <gtest/gtest.h>
#include "data/Color.h"
#include "TestingUtils.h"

using namespace testing;

class ColorTest : public Test {
protected:
    void SetUp() override {
        disableLogger();
    }
};

TEST_F(ColorTest, RGBColorEquality) {
    auto first = RGBColor{0, 0, 0};
    auto second = RGBColor{0, 0, 0};
    EXPECT_EQ(first, second);
    first = RGBColor{1, 0, 0};
    second = RGBColor{0, 0, 0};
    EXPECT_NE(first, second);
    first = RGBColor{0, 1, 0};
    second = RGBColor{0, 0, 0};
    EXPECT_NE(first, second);
    first = RGBColor{0, 0, 1};
    second = RGBColor{0, 0, 0};
    EXPECT_NE(first, second);
}

TEST_F(ColorTest, HSLColorEquality) {
    auto first = HSLColor{0, 0, 0};
    auto second = HSLColor{0, 0, 0};
    EXPECT_EQ(first, second);
    first = HSLColor{1, 0, 0};
    second = HSLColor{0, 0, 0};
    EXPECT_NE(first, second);
    first = HSLColor{0, 1, 0};
    second = HSLColor{0, 0, 0};
    EXPECT_NE(first, second);
    first = HSLColor{0, 0, 1};
    second = HSLColor{0, 0, 0};
    EXPECT_NE(first, second);
}

TEST_F(ColorTest, ConvertHSLToRGBOutOfBounds) {
    EXPECT_THROW(convertHSLToRGB({400, 0, 0}), out_of_range);
    EXPECT_THROW(convertHSLToRGB({0, 200, 0}), out_of_range);
    EXPECT_THROW(convertHSLToRGB({0, 0, 150}), out_of_range);
}

TEST_F(ColorTest, ConvertHSLToRGBBlack) {
    auto expected = RGBColor{0, 0, 0};
    EXPECT_EQ(convertHSLToRGB({18, 0, 0}), expected);
}

TEST_F(ColorTest, ConvertHSLToRGBWhite) {
    auto expected = RGBColor{255, 255, 255};
    EXPECT_EQ(convertHSLToRGB({18, 0, 100}), expected);
}

TEST_F(ColorTest, ConvertHSLToRGBSuccess) {
    auto expected = RGBColor{190, 131, 131};
    EXPECT_EQ(convertHSLToRGB({0, 31, 63}), expected);
    expected = RGBColor{171, 190, 131};
    EXPECT_EQ(convertHSLToRGB({79, 31, 63}), expected);
    expected = RGBColor{131, 190, 152};
    EXPECT_EQ(convertHSLToRGB({141, 31, 63}), expected);
    expected = RGBColor{131, 167, 190};
    EXPECT_EQ(convertHSLToRGB({203, 31, 63}), expected);
    expected = RGBColor{152, 131, 190};
    EXPECT_EQ(convertHSLToRGB({261, 31, 63}), expected);
    expected = RGBColor{190, 131, 172};
    EXPECT_EQ(convertHSLToRGB({318, 31, 63}), expected);
    expected = RGBColor{190, 131, 131};
    EXPECT_EQ(convertHSLToRGB({360, 31, 63}), expected);
}
