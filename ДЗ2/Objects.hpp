#pragma once
#include <memory>
#include <string>
#include <iostream>

// ============================================================
// 1. ХАРАКТЕРИСТИКИ
// ============================================================

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

// ============================================================
// 2. ДЕРЕВО НАСЛЕДОВАНИЯ
// ============================================================

class Object {
protected:
    std::string id_;
    std::string name_;
    std::string type_;
    std::shared_ptr<ModelSpec> model_;
public:
    Object() = default;
    virtual ~Object() = default;

    virtual std::string inventoryId() { return id_; }
    virtual std::string name() { return name_; }
    virtual std::string describe() { return name_ + " " + id_; }

    std::string type() { return type_; }
    std::shared_ptr<ModelSpec> model() { return model_; }

    friend std::ostream& operator<<(std::ostream& os, Object& object) {
        return os << object.describe();
    }
    friend bool operator<(Object& a, Object& b) {
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
