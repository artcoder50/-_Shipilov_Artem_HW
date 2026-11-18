#include "Service.hpp"
#include "Errors.hpp"
#include <algorithm>
#include <memory>

Object* Service::findById(const std::string& id) {
    auto it = byId_.find(id);
    if (it == byId_.end()) {
        throw NotFoundError("id not found: " + id);
    }
    return it->second;
}

std::shared_ptr<ModelSpec> Service::getOrCreateModel(
        const std::string& name, int score, double energy) {
    auto it = models_.find(name);
    if (it != models_.end()) {
        return it->second;
    }
    auto spec = std::make_shared<ModelSpec>(name, score, energy);
    models_[name] = spec;
    return spec;
}

void Service::registerUnit(std::unique_ptr<Object> unit) {
    Object* raw = unit.get();
    byId_[raw->inventoryId()] = raw;
    items_.push_back(std::move(unit));
}

void Service::addScooter(const std::string& id, const std::string& name,
                         const std::string& model, double energy, int score) {
    inspector_.inspect(id, name, energy, score, byId_);

    auto spec = getOrCreateModel(model, score, energy);
    registerUnit(std::make_unique<ElectricScooter>(id, name, spec));
}

void Service::addBike(const std::string& id, const std::string& name,
                      const std::string& model, int score) {
    inspector_.inspect(id, name, score, byId_);

    auto spec = getOrCreateModel(model, score, 0.0);
    registerUnit(std::make_unique<Bike>(id, name, score, spec));
}

void Service::addEbike(const std::string& id, const std::string& name,
                       const std::string& model, double energy, int score) {
    inspector_.inspect(id, name, energy, score, byId_);

    auto spec = getOrCreateModel(model, score, energy);
    registerUnit(std::make_unique<Ebike>(id, name, spec));
}

void Service::addHelmet(const std::string& id, const std::string& name) {
    inspector_.inspect(id, name, byId_);
    registerUnit(std::make_unique<Helmet>(id, name));
}

void Service::addDock(const std::string& id, const std::string& name,
                      double energy) {
    inspector_.inspect(id, name, energy, byId_);
    registerUnit(std::make_unique<Dock>(id, name, energy));
}

double Service::totalEnergy() {
    double sum = 0.0;
    for (auto& item : items_) {
        if (auto* ec = dynamic_cast<EnergyConsumer*>(item.get())) {
            sum += ec->dailyEnergy();
        }
    }
    return sum;
}

std::vector<Vehicle*> Service::noviceList(int min) {
    std::vector<Vehicle*> res;
    for (auto& item : items_) {
        if (auto* v = dynamic_cast<Vehicle*>(item.get())) {
            if (v->score() >= min) {
                res.push_back(v);
            }
        }
    }
    return res;
}

void Service::printAll(std::ostream& os) {
    std::vector<Object*> refs;
    refs.reserve(items_.size());
    for (auto& item : items_) {
        refs.push_back(item.get());
    }

    std::sort(refs.begin(), refs.end(),
              [](Object* a, Object* b) { return *a < *b; });

    for (auto* o : refs) {
        os << *o << '\n';
    }
}

void Service::printModels(std::ostream& os) {
    for (auto& [name, spec] : models_) {
        os << *spec << '\n';
    }
}

void Service::focus(const std::string& id) {
    Object* obj = findById(id);
    auto model = obj->model();
    if (model) {
        focus_.set(model);
    } else {
        focus_.reset();
    }
}

void Service::clearFocus() {
    focus_.reset();
}

std::string Service::showFocus() {
    return focus_.show();
}

void Service::remove(const std::string& id) {
    Object* obj = findById(id);
    auto model = obj->model();

    byId_.erase(id);
    items_.erase(
        std::remove_if(items_.begin(), items_.end(),
                       [obj](const auto& p) { return p.get() == obj; }),
        items_.end());

    if (model) {
        bool used = false;
        for (auto& item : items_) {
            if (item->model() == model) {
                used = true;
                break;
            }
        }
        if (!used) {
            for (auto it = models_.begin(); it != models_.end(); ++it) {
                if (it->second == model) {
                    models_.erase(it);
                    break;
                }
            }
        }
    }
}

ElectricScooter* Service::mostPoverfulScooter() {
    ElectricScooter* best = nullptr;
    double bestE = -1.0;
    for (auto& item : items_) {
        if (auto* s = dynamic_cast<ElectricScooter*>(item.get())) {
            double e = s->dailyEnergy();
            if (e > bestE) { bestE = e; best = s; }
        }
    }
    return best;
}

Ebike* Service::mostPoverfulEbike() {
    Ebike* best = nullptr;
    double bestE = -1.0;
    for (auto& item : items_) {
        if (auto* s = dynamic_cast<Ebike*>(item.get())) {
            double e = s->dailyEnergy();
            if (e > bestE) { bestE = e; best = s; }
        }
    }
    return best;
}

Dock* Service::mostPoverfulDock() {
    Dock* best = nullptr;
    double bestE = -1.0;
    for (auto& item : items_) {
        if (auto* d = dynamic_cast<Dock*>(item.get())) {
            double e = d->dailyEnergy();
            if (e > bestE) { bestE = e; best = d; }
        }
    }
    return best;
}
