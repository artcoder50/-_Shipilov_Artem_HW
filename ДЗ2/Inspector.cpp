#include "Inspector.hpp"
#include "Errors.hpp"
#include "Objects.hpp"
#include <algorithm>
#include <cctype>

void Inspector::checkId(
        const std::string& id,
        const std::unordered_map<std::string, Object*>& items) const {
    if (id.empty()) {
        throw ParseError("empty id");
    }
    if (items.count(id)) {
        throw ParseError("duplicate id: " + id);
    }
}

void Inspector::checkScore(int score) const {
    if (score < 1 || score > 10) {
        throw ParseError("score out of range 1..10: " + std::to_string(score));
    }
}

void Inspector::checkEnergy(double e) const {
    if (e < 0.0) {
        throw ParseError("negative energy: " + std::to_string(e));
    }
}

void Inspector::checkName(const std::string& name) const {
    std::string lower = name;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lower.find(flag_) != std::string::npos) {
        throw InspectionError("inspection rejected " + name);
    }
}

void Inspector::inspect(
        const std::string& id, const std::string& name,
        double energy, int score,
        const std::unordered_map<std::string, Object*>& items) const {
    checkId(id, items);
    checkEnergy(energy);
    checkScore(score);
    checkName(name);
}

void Inspector::inspect(
        const std::string& id, const std::string& name,
        int score,
        const std::unordered_map<std::string, Object*>& items) const {
    checkId(id, items);
    checkScore(score);
}

void Inspector::inspect(
        const std::string& id, const std::string& name,
        double energy,
        const std::unordered_map<std::string, Object*>& items) const {
    checkId(id, items);
    checkEnergy(energy);
}

void Inspector::inspect(
        const std::string& id, const std::string& name,
        const std::unordered_map<std::string, Object*>& items) const {
    checkId(id, items);
}
