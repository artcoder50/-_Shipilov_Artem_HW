#pragma once
#include <stdexcept>

class InspectionError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class ParseError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class NotFoundError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};
