#pragma once
#include <string>
#include <unordered_map>

class Object;

class Inspector {
    std::string flag_ = "broken";

    void checkId(const std::string& id,
                 const std::unordered_map<std::string, Object*>& items) const;
    void checkScore(int score) const;
    void checkEnergy(double e) const;
    void checkName(const std::string& name) const;

public:
    void inspect(const std::string& id, const std::string& name,
                 double energy, int score,
                 const std::unordered_map<std::string, Object*>& items) const;
    void inspect(const std::string& id, const std::string& name,
                 int score,
                 const std::unordered_map<std::string, Object*>& items) const;
    void inspect(const std::string& id, const std::string& name,
                 double energy,
                 const std::unordered_map<std::string, Object*>& items) const;
    void inspect(const std::string& id, const std::string& name,
                 const std::unordered_map<std::string, Object*>& items) const;
};
