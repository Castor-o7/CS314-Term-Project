#include "Provider.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>

// Default constructor
Provider::Provider() : name(""), number(""), streetAddress(""), city(""), state(""), zipCode("") {
    // Empty default constructor for map compatibility
}

// Validation helper methods
bool Provider::validateNumber(const std::string& number) {
    return number.length() == 9 && std::all_of(number.begin(), number.end(), ::isdigit);
}

bool Provider::validateState(const std::string& state) {
    return state.length() == 2 && std::all_of(state.begin(), state.end(), ::isalpha);
}

bool Provider::validateZipCode(const std::string& zipCode) {
    return zipCode.length() == 5 && std::all_of(zipCode.begin(), zipCode.end(), ::isdigit);
}

// Constructor
Provider::Provider(const std::string& name, const std::string& number, const std::string& streetAddress,
                   const std::string& city, const std::string& state, const std::string& zipCode)
    : name(name), streetAddress(streetAddress), city(city), state(state), zipCode(zipCode) {
    if (!validateNumber(number)) {
        throw std::invalid_argument("Provider number must be exactly 9 digits.");
    }
    if (!validateState(state)) {
        throw std::invalid_argument("State must be exactly 2 characters.");
    }
    if (!validateZipCode(zipCode)) {
        throw std::invalid_argument("ZipCode must be exactly 5 digits.");
    }
    this->number = number;
}

// Update provider details
void Provider::updateDetails(const std::string& streetAddress, const std::string& city, 
                            const std::string& state, const std::string& zipCode) {
    if (!validateState(state)) {
        throw std::invalid_argument("State must be exactly 2 characters.");
    }
    if (!validateZipCode(zipCode)) {
        throw std::invalid_argument("ZipCode must be exactly 5 digits.");
    }
    this->streetAddress = streetAddress;
    this->city = city;
    this->state = state;
    this->zipCode = zipCode;
}

// File I/O
void Provider::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::app);
    ofs << name << ',' << number << ',' << streetAddress << ',' << city << ',' << state << ',' << zipCode << '\n';
}

std::vector<Provider> Provider::loadFromFile(const std::string& filename) {
    std::vector<Provider> providers;
    std::ifstream ifs(filename);
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string name, number, streetAddress, city, state, zipCode;
        std::getline(ss, name, ',');
        std::getline(ss, number, ',');
        std::getline(ss, streetAddress, ',');
        std::getline(ss, city, ',');
        std::getline(ss, state, ',');
        std::getline(ss, zipCode, ',');
        try {
            providers.emplace_back(name, number, streetAddress, city, state, zipCode);
        } catch (...) { /* skip invalid lines */ }
    }
    return providers;
}
