#include "Units.hpp"
#include <utility>

Helmet::Helmet(std::string id, std::string name) {
    id_   = std::move(id);
    name_ = std::move(name);
    type_ = "helmet";
}

Dock::Dock(std::string id, std::string name, double energy) {
    id_     = std::move(id);
    name_   = std::move(name);
    type_   = "dock";
    energy_ = energy;
}

Bike::Bike(std::string id, std::string name, int score,
           std::shared_ptr<ModelSpec> model) {
    id_    = std::move(id);
    name_  = std::move(name);
    type_  = "bike";
    score_ = score;
    model_ = std::move(model);
}

ElectricScooter::ElectricScooter(std::string id, std::string name,
                                 std::shared_ptr<ModelSpec> model) {
    id_    = std::move(id);
    name_  = std::move(name);
    type_  = "scooter";
    model_ = std::move(model);
}

Ebike::Ebike(std::string id, std::string name,
             std::shared_ptr<ModelSpec> model) {
    id_    = std::move(id);
    name_  = std::move(name);
    type_  = "ebike";
    model_ = std::move(model);
}
