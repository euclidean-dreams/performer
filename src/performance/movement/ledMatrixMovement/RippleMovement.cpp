#include <performance/action/ledMatrixAction/RippleAction.h>
#include "RippleMovement.h"

namespace performer {

RippleMovement::RippleMovement(LedMatrixProxy &ledMatrix, impresarioUtils::RandomNumberGenerator &randomNumberGenerator)
        : LedMatrixMovement(ledMatrix, randomNumberGenerator),
          previousDisplaySignal{},
          previousSumEnergyDelta{0},
          effectThreshold{0.5},
          rippleSpeed{0.5},
          maxTotalRipples{1000} {

}

void RippleMovement::handleIncomingPacket(const impresarioUtils::Packet &packet) {
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::floatMorsel) {
        auto morsel = packet.getFloatMorsel();
        if (morsel->field() == 11) {
            effectThreshold = morsel->value() * 0.7;
        } else if (morsel->field() == 12) {
            rippleSpeed = morsel->value() * 2;
        }
    }
    if (packet.getIdentifier() == ImpresarioSerialization::Identifier::displaySignal) {
        auto rawDisplaySignal = packet.getDisplaySignal();
        auto samples = rawDisplaySignal->samples();
        if (previousDisplaySignal.empty()) {
            previousDisplaySignal.resize(samples->size());
        }
        auto rippleOrigins = calculateRippleOrigins(samples);
        for (auto rippleOrigin: *rippleOrigins) {
            auto hue = randomNumberGenerator.generate(HSL_HUE_MAX);
            auto color = HSLColor{static_cast<uint32_t>(hue), 100, 50};
            auto action = std::make_unique<RippleAction>(
                    ledMatrix, color, std::get<0>(rippleOrigin), std::get<1>(rippleOrigin), rippleSpeed
            );
            actionCollection.addAction(move(action));
        }
        actionCollection.trimActions(maxTotalRipples);

        // record current signal
        for (int index = 0; index < samples->size(); index++) {
            previousDisplaySignal[index] = (*samples)[index];
        }
    }
}

std::unique_ptr<std::vector<std::tuple<int, int>>> RippleMovement::calculateRippleOrigins(
        const flatbuffers::Vector<float> *samples) {
    auto rippleOrigins = std::make_unique<std::vector<std::tuple<int, int>>>();
    auto sumEnergyDelta = 0;
    auto maxDerivative = 0;
    auto maxDerivativeIndex = 0;
    for (int index = 0; index < samples->size(); index++) {
        auto sample = (*samples)[index];
        // accommodate for crazy large last sample - this will go once those ridiculous triangular filters are changed
        if (index == samples->size() - 1) {
            sample /= 100;
        }
        auto derivative = sample - previousDisplaySignal[index];
        if (derivative > maxDerivative) {
            maxDerivative = derivative;
            maxDerivativeIndex = index;
        }
        if (derivative > 0) {
            sumEnergyDelta += derivative;
        }
    }
    if (sumEnergyDelta > previousSumEnergyDelta * 10 * effectThreshold) {
        auto x = maxDerivativeIndex % ledMatrix.width();
        auto y = floor(maxDerivativeIndex / ledMatrix.width());
        rippleOrigins->push_back({x, y});
    }
    previousSumEnergyDelta = sumEnergyDelta;
    return rippleOrigins;
}

void RippleMovement::handleTick() {

}

}
