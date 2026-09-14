#include <syncstream>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <sstream>
#include "ucioption.h"

namespace athena {

UCIOption::UCIOption(Callback cb) :
    type("button"),
    callback(std::move(cb)) {}   

UCIOption::UCIOption(bool value, Callback cb) : 
    type("check"),
    callback(std::move(cb)) {
    default_value = current_value = (value ? "true" : "false"); }

UCIOption::UCIOption(int value, int min, int max, Callback cb) :
    type("spin"),
    min(min),
    max(max), 
    callback(std::move(cb)) {
    default_value = current_value = std::to_string(value); }

UCIOption::UCIOption(const char* value, Callback cb) :
    type("string"),
    callback(std::move(cb)) {
    default_value = current_value = value; }

UCIOption::UCIOption(const char* values, const char* current, Callback cb) :
    type("combo"),
    callback(std::move(cb)) {
    default_value = values;
    current_value = current; }

UCIOption::operator int() const {
    assert(type == "spin");
    return std::stoi(current_value);
}

UCIOption::operator bool() const {
    assert(type == "check");
    return current_value == "true";
}

UCIOption::operator std::string() const {
    assert(type == "string");
    return current_value;
}

bool UCIOption::operator==(const char* s) const {
    assert(type == "combo");
    return current_value == s;
}

bool UCIOption::operator!=(const char* s) const {
    return !(*this == s);
}

UCIOption& UCIOption::operator=(const std::string& value) {
    current_value = value;
    if (callback) {
        callback(*this);
    }
    return *this;
}

void Options::addoption(std::string name, UCIOption option) {
    if (!map.emplace(std::move(name), std::move(option)).second) {
        throw std::runtime_error("Option already exists");
    }
}

void Options::setoption(std::istream& is) {
    std::string token, name, value;

    is >> token;

    while (is >> token && token != "value") name  += ( name.empty() ? "" : " ") + token;
    while (is >> token)                     value += (value.empty() ? "" : " ") + token;

    if (map.contains(name))
        map[name] = value;
    else
        std::osyncstream(std::cout) << "No such option: " << name << std::endl;
}

std::ostream& operator<<(std::ostream& os, const UCIOption& option) {

    os << " type " 
       << option.type
       << " default " 
       << option.default_value;

    if (option.type == "spin") {
        os << " min " << option.min << " max " << option.max;
    } else if (option.type == "combo") { 
        std::istringstream ss;
        std::string value;
        
        while (ss >> value) {
            os << " var " << value;
        }
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const Options& options) {
    for (const auto& [name, option] : options.map) {
        os << "option name " 
           << name 
           << option
           << "\n";
    }
    return os;
}

} // namespace athena