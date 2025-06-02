#include "Service.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>

// Default constructor
Service::Service() : code(""), name(""), fee(0.0) {
    // Empty default constructor for map compatibility
}

// Validation helper methods
bool Service::validateCode(const std::string& code) {
    return code.length() == 6 && std::all_of(code.begin(), code.end(), ::isdigit);
}

bool Service::validateFee(double fee) {
    return fee >= 0.0 && fee <= 999.99;
}

// Constructor
Service::Service(const std::string& code, const std::string& name, double fee)
    : name(name) {
    if (!validateCode(code)) {
        throw std::invalid_argument("Service code must be exactly 6 digits.");
    }
    if (!validateFee(fee)) {
        throw std::invalid_argument("Fee must be between 0 and 999.99.");
    }
    this->code = code;
    this->fee = fee;
}

// Set fee
void Service::setFee(double newFee) {
    if (!validateFee(newFee)) {
        throw std::invalid_argument("Fee must be between 0 and 999.99.");
    }
    fee = newFee;
}

// File I/O
void Service::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::app);
    ofs << code << ',' << name << ',' << fee << '\n';
}

std::vector<Service> Service::loadFromFile(const std::string& filename) {
    std::vector<Service> services;
    std::ifstream ifs(filename);
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string code, name, feeStr;
        std::getline(ss, code, ',');
        std::getline(ss, name, ',');
        std::getline(ss, feeStr, ',');
        double fee = std::stod(feeStr);
        try {
            services.emplace_back(code, name, fee);
        } catch (...) { /* skip invalid lines */ }
    }
    return services;
}
