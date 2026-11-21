#include "Units.hpp"

Helmet::Helmet(std::string id, std::string name) {
    id_   = id;
    name_ = name;
    type_ = "helmet";
}

Dock::Dock(std::string id, std::string name, double energy) {
    id_     = id;
    name_   = name;
    type_   = "dock";
    energy_ = energy;
}

Bike::Bike(std::string id, std::string name, int score,
           std::shared_ptr<ModelSpec> model) {
    id_    = id;
    name_  = name;
    type_  = "bike";
    score_ = score;
    model_ = model;
}

ElectricScooter::ElectricScooter(std::string id, std::string name,
                                 std::shared_ptr<ModelSpec> model) {
    id_    = id;
    name_  = name;
    type_  = "scooter";
    model_ = model;
}

Ebike::Ebike(std::string id, std::string name,
             std::shared_ptr<ModelSpec> model) {
    id_    = id;
    name_  = name;
    type_  = "ebike";
    model_ = model;
}
