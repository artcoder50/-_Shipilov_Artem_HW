#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include "Service.hpp"

class API {
    using Method = std::function<void(std::vector<std::string>&)>;

    Service& service_;
    bool running_ = true;
    std::unordered_map<std::string, Method> methods_;

    void buildMethods();
    void readCommand();
    void printError(const std::string& msg);

public:
    API(Service& service) : service_(service) { buildMethods(); }
    void run();
};
