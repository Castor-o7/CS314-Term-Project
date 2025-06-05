#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>
#include <vector>
#include "googletest/googletest/include/gtest/gtest.h"

class Provider {
private:
    std::string name;          // 25 characters
    std::string number;        // 9 digits
    std::string streetAddress; // 25 characters
    std::string city;          // 14 characters
    std::string state;         // 2 characters
    std::string zipCode;       // 5 digits

    // Validation helper methods
    static bool validateNumber(const std::string& number);
    static bool validateState(const std::string& state);
    static bool validateZipCode(const std::string& zipCode);

public:
    // Default constructor
    Provider();
    
    // Constructor
    Provider(const std::string& name, const std::string& number, const std::string& streetAddress,
             const std::string& city, const std::string& state, const std::string& zipCode);

    // Update provider details
    void updateDetails(const std::string& streetAddress, const std::string& city, 
                      const std::string& state, const std::string& zipCode);

    // Getters
    std::string getName() const { return name; }
    std::string getNumber() const { return number; }
    std::string getStreetAddress() const { return streetAddress; }
    std::string getCity() const { return city; }
    std::string getState() const { return state; }
    std::string getZipCode() const { return zipCode; }

    void saveToFile(const std::string& filename) const;
    static std::vector<Provider> loadFromFile(const std::string& filename);
};

#endif // PROVIDER_H
