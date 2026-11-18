#pragma once
#include "Objects.hpp"

class Helmet : public Inventory {
public:
    Helmet(std::string id, std::string name);
    ~Helmet() = default;
};

class Dock : public ElectricItem {
    double energy_;
public:
    Dock(std::string id, std::string name, double energy);
    ~Dock() = default;
    double dailyEnergy() { return energy_; }
};

class Bike : public Vehicle {
    int score_;
public:
    Bike(std::string id, std::string name, int score,
         std::shared_ptr<ModelSpec> model = nullptr);
    ~Bike() = default;
    int score() { return score_; }
};

class ElectricScooter : public ElectricVehicle {
public:
    ElectricScooter(std::string id, std::string name,
                    std::shared_ptr<ModelSpec> model);
    ~ElectricScooter() = default;
};

class Ebike : public ElectricVehicle {
public:
    Ebike(std::string id, std::string name,
          std::shared_ptr<ModelSpec> model);
    ~Ebike() = default;
};
