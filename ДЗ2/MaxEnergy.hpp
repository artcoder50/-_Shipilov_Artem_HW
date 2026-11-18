#pragma once
#include <memory>
#include <vector>
#include "Objects.hpp"

template<typename T>
T* mostPowerful(const std::vector<std::shared_ptr<T>>& items) {
    T* best = nullptr;
    double bestE = -1.0;

    for (const auto& p : items) {
        auto* ec = dynamic_cast<EnergyConsumer*>(p.get());
        if (!ec) continue;

        double e = ec->dailyEnergy();
        if (e > bestE) {
            bestE = e;
            best = p.get();
        }
    }

    return best;
}
