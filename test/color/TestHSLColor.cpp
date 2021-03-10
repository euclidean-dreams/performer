#include <gtest/gtest.h>
#include <RGBColor_generated.h>
#include "color/HSLColor.h"

namespace performer {

class HSLColorTest : public testing::Test {
protected:
    inline static void constructorWrapper(uint32_t hue, uint8_t saturation, uint8_t lightness) {
        HSLColor{hue, saturation, lightness};
    }

    inline static bool areEqual(ImpresarioSerialization::RGBColor first, ImpresarioSerialization::RGBColor second) {
        return first.red() == second.red()
               && first.green() == second.green()
               && first.blue() == second.blue();
    }
};

TEST_F(HSLColorTest, InvalidColor) {
    EXPECT_THROW(constructorWrapper(400, 0, 0), std::out_of_range);
    EXPECT_THROW(constructorWrapper(0, 200, 0), std::out_of_range);
    EXPECT_THROW(constructorWrapper(0, 0, 150), std::out_of_range);
}

TEST_F(HSLColorTest, ConvertToRGBBasic) {
    auto input = HSLColor{0, 31, 63};
    auto expected = ImpresarioSerialization::RGBColor{190, 131, 131};
    EXPECT_TRUE(areEqual(input.convertToRGB(), expected));
    input = HSLColor{79, 31, 63};
    expected = ImpresarioSerialization::RGBColor{171, 190, 131};
    EXPECT_TRUE(areEqual(input.convertToRGB(), expected));
    input = HSLColor{141, 31, 63};
    expected = ImpresarioSerialization::RGBColor{131, 190, 152};
    EXPECT_TRUE(areEqual(input.convertToRGB(), expected));
    input = HSLColor{203, 31, 63};
    expected = ImpresarioSerialization::RGBColor{131, 167, 190};
    EXPECT_TRUE(areEqual(input.convertToRGB(), expected));
    input = HSLColor{261, 31, 63};
    expected = ImpresarioSerialization::RGBColor{152, 131, 190};
    EXPECT_TRUE(areEqual(input.convertToRGB(), expected));
    input = HSLColor{318, 31, 63};
    expected = ImpresarioSerialization::RGBColor{190, 131, 172};
    EXPECT_TRUE(areEqual(input.convertToRGB(), expected));
    input = HSLColor{360, 31, 63};
    expected = ImpresarioSerialization::RGBColor{190, 131, 131};
    EXPECT_TRUE(areEqual(input.convertToRGB(), expected));
}

TEST_F(HSLColorTest, ConvertToRGBBlack) {
    auto input = HSLColor{0, 0, 0};
    auto expected = ImpresarioSerialization::RGBColor{0, 0, 0};
    EXPECT_TRUE(areEqual(input.convertToRGB(), expected));
}

TEST_F(HSLColorTest, ConvertToRGBWhite) {
    auto input = HSLColor{0, 0, 100};
    auto expected = ImpresarioSerialization::RGBColor{255, 255, 255};
    EXPECT_TRUE(areEqual(input.convertToRGB(), expected));
}

}
