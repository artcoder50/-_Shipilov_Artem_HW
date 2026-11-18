#pragma once
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Focus.hpp"
#include "Inspector.hpp"
#include "MaxEnergy.hpp"
#include "Objects.hpp"
#include "Units.hpp"

class Service {
  std::vector<std::unique_ptr<Object>> items_;
  std::unordered_map<std::string, Object*> byId_;
  std::unordered_map<std::string, std::shared_ptr<ModelSpec>> models_;
  Focus focus_;
  Inspector inspector_;

  Object* findById(const std::string& id);
  std::shared_ptr<ModelSpec> getOrCreateModel(const std::string& name,
                                              int score, double energy);
  void registerUnit(std::unique_ptr<Object> unit);

 public:
  void addScooter(const std::string& id, const std::string& name,
                  const std::string& model, double energy, int score);
  void addBike(const std::string& id, const std::string& name,
               const std::string& model, int score);
  void addEbike(const std::string& id, const std::string& name,
                const std::string& model, double energy, int score);
  void addHelmet(const std::string& id, const std::string& name);
  void addDock(const std::string& id, const std::string& name, double energy);

  double totalEnergy();
  std::vector<Vehicle*> noviceList(int min = 6);
  void printAll(std::ostream& os);
  void printModels(std::ostream& os);

  void focus(const std::string& id);
  void clearFocus();
  std::string showFocus();
  void remove(const std::string& id);

  ElectricScooter* mostPoverfulScooter();
  Ebike* mostPoverfulEbike();
  Dock* mostPoverfulDock();
};
