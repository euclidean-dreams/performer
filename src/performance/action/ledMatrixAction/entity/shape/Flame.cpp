#include "Flame.h"

namespace performer {

Flame::Flame(Coordinate origin, HSLColor rootColor, int width, int height)
        : Shape{origin, rootColor, calculateBoundingBox(origin, width, height)},
          width{width},
          height{height},
          initialColor{rootColor},
          flickerPhase{0},
          flickerMagnitude{1},
          flickerPhaseDirection{true},
          flickerMagnitudeDirection{true} {
}

bool Flame::coordinateInShape(Coordinate coordinate) {
    auto x = coordinate.x - origin.x;
    auto y = coordinate.y - origin.y;
    auto upperBoundIntermediary = exp(-(y * y) / (2 * std::pow(height / 2, 2)));
    auto gaussianBound = width * upperBoundIntermediary - width / 1.5;
    auto flickerBound = flickerMagnitude * std::sin(y + flickerPhase);
    bool underUpperBound = x < gaussianBound - flickerBound;
    if (underUpperBound) {
        auto lowerBoundIntermediary = exp(-(y * y) / (2 * std::pow(height / 2, 2)));
        bool aboveLowerBound = x > -(width / 2) * lowerBoundIntermediary + width / 4;
        if (aboveLowerBound) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

HSLColor Flame::calculateColor(Coordinate coordinate) {
    return rootColor;
}

void Flame::grow() {

}

void Flame::shrink() {

}

void Flame::flicker(impresarioUtils::RandomNumberGenerator &randomNumberGenerator, float intensity) {
    auto chanceOfChange = 10;

    // phase
    if (randomNumberGenerator.generate(chanceOfChange) == 0) {
        flickerPhaseDirection = !flickerPhaseDirection;
    }
    auto phaseAdjustment = randomNumberGenerator.generateProportion() * intensity;
    if (flickerPhaseDirection) {
        flickerPhase += phaseAdjustment;
    } else {
        flickerPhase -= phaseAdjustment;
    }

    // magnitude
    if (randomNumberGenerator.generate(chanceOfChange) == 0) {
        flickerMagnitudeDirection = !flickerMagnitudeDirection;
    }
    auto magnitudeAdjustment = randomNumberGenerator.generateProportion() * intensity * 3;
    if (flickerMagnitudeDirection) {
        flickerMagnitude += magnitudeAdjustment;
    } else {
        flickerMagnitude -= magnitudeAdjustment;
    }
    if (flickerMagnitude > height / 4) {
        flickerMagnitude = height / 4;
    }
    if (flickerMagnitude < -height / 4) {
        flickerMagnitude = -height / 4;
    }

    // color
    int currentHue = rootColor.getHue();
    int hue = currentHue + randomNumberGenerator.generate(5) * intensity;
    if (hue - static_cast<int>(initialColor.getHue()) > 15) {
        hue = currentHue;
    }
    setRootColor(
            {LedGizmos::bindHue(hue), rootColor.getSaturation(), static_cast<uint8_t>(rootColor.getLightness())}
    );
}

}
