#include "RippleMovement.h"

RippleMovement::RippleMovement(LedMatrixProxy &ledMatrix, RandomNumberGenerator &randomNumberGenerator)
        : ledMatrix{ledMatrix},
          randomNumberGenerator{randomNumberGenerator},
          actions{},
          lastColor{0, 0, 0},
          mode{0} {

}

void RippleMovement::handleEvent(const Event &event) {
    if (dynamic_cast<const OnsetEvent *>(&event) != nullptr) {
        auto &onsetEvent = dynamic_cast<const OnsetEvent &>(event);
        createRipple(onsetEvent);
    }
}

void RippleMovement::createRipple(const OnsetEvent &event) {
    Color::HSLColor color = generateRippleColor();
    lastColor = color;
    std::unique_ptr<Action> ripple;
    if (mode == 0) {
        auto index = randomNumberGenerator.generate(ledMatrix.size());
        ripple = make_unique<Ripple>(ledMatrix, index, color, 0.2);
    } else {
        ripple = make_unique<Ripple>(ledMatrix, ledMatrix.size() / 2, color, 0.2);
    }
    actions.push_back(move(ripple));
}

Color::HSLColor RippleMovement::generateRippleColor() {
    auto hue = static_cast<uint32_t>(randomNumberGenerator.generate(361));
    while (abs(static_cast<int>(hue - lastColor.getHue())) < 60) {
        hue = static_cast<uint32_t>(randomNumberGenerator.generate(361));
    }
    auto color = Color::HSLColor{hue, 100, 50};
    return color;
}

void RippleMovement::conduct() {
    auto iterator = actions.begin();
    while (iterator != actions.end()) {
        (*iterator)->execute();
        if ((*iterator)->finished()) {
            iterator = actions.erase(iterator);
        } else {
            iterator++;
        }
    }
}