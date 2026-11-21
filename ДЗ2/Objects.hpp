#pragma once
#include <memory>
#include <string>
#include <iostream>


class ModelSpec {
    std::string name_;
    int         score_;
    double      energy_;
public:
    ModelSpec(std::string name, int score, double energy)
        : name_(std::move(name)), score_(score), energy_(energy) {}

    const std::string& name()  { return name_; }
    int    score()  { return score_; }
    double energy() { return energy_; }

    std::string describe() {
        return name_ + "(score=" + std::to_string(score_) +
               ", energy=" + std::to_string(energy_) + ")";
    }
    friend std::ostream& operator<<(std::ostream& os, ModelSpec& m) {
        return os << m.describe();
    }
};

class EnergyConsumer {
public:
    EnergyConsumer() = default;
    virtual ~EnergyConsumer() = default;
    virtual double dailyEnergy() = 0;
};

class ObstractObject {
public:
    virtual ~ObstractObject() = default;

    virtual std::string inventoryId() = 0;
    virtual std::string name()        = 0;
    virtual std::string describe()    = 0;
};

class Object : public ObstractObject {
protected:
    std::string id_;
    std::string name_;
    std::string type_;
    std::shared_ptr<ModelSpec> model_;

public:
    Object() = default;
    ~Object() = default;

    std::string inventoryId() { return id_; }
    std::string name()        { return name_; }
    std::string describe()    { return id_ + " " + name_; }

    std::string type() { return type_; }
    std::shared_ptr<ModelSpec> model() { return model_; }

    friend std::ostream& operator<<(std::ostream& os, ObstractObject& o) {
        return os << o.describe();
    }
    friend bool operator<(ObstractObject& a, ObstractObject& b) {
        return a.inventoryId() < b.inventoryId();
    }
};

class Inventory : public Object {
public:
    ~Inventory() = default;
};

class Vehicle : public Object {
public:
    ~Vehicle() = default;
    virtual int score() = 0;
};

class ElectricItem : public Inventory, public EnergyConsumer {
public:
    ~ElectricItem() = default;
};

class ElectricVehicle : public Vehicle, public EnergyConsumer {
public:
    ~ElectricVehicle() = default;
    int score() { return model_ ? model_->score() : 0; }
    double dailyEnergy() { return model_ ? model_->energy() : 0.0; }
};
