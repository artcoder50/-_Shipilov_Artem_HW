#pragma once
#include <memory>
#include <string>
#include "Objects.hpp"

class Focus {
    std::weak_ptr<ModelSpec> ptr_;
public:
    void set(std::shared_ptr<ModelSpec> p) { ptr_ = p; }
    void reset() { ptr_.reset(); }
    std::shared_ptr<ModelSpec> lock() { return ptr_.lock(); }

    std::string show() {
        if (auto sp = ptr_.lock()) return sp->describe();
        return "expired";
    }
};
