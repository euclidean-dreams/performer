#include "DragonCurveTraceAction.h"

namespace performer {

DragonCurveTraceAction::DragonCurveTraceAction(LedMatrixProxy &ledMatrix,
                                               impresarioUtils::RandomNumberGenerator &randomNumberGenerator,
                                               Coordinate origin, HSLColor color,
                                               float speed, double scale)
        : LedMatrixAction(ledMatrix),
          speed{speed},
          currentLightness{static_cast<float>(color.getLightness())} {
    double orientation = randomNumberGenerator.generateProportion() * 2 * M_PI;
    entity = std::make_unique<DragonCurve>(origin, color, orientation, 10, scale);
}

bool DragonCurveTraceAction::finished() {
    return currentLightness == 0;
}

void DragonCurveTraceAction::handleTick() {
    if (tick % static_cast<int>(5 - 3 * speed) == 0) {
        currentLightness--;
        if (currentLightness < 0) {
            currentLightness = 0;
        }
        auto currentColor = entity->getRootColor();
        entity->setRootColor(
                {currentColor.getHue(), currentColor.getSaturation(), static_cast<uint8_t>(currentLightness)}
        );
    }
    for (int i = 0; i < speed * 10; i++) {
        entity->tick();
    }
    entity->render(ledMatrix);
}

}
