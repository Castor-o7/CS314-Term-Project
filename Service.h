#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>
#include "googletest/googletest/include/gtest/gtest.h"

class Service {
private:
    std::string code; // 6 digits
    std::string name; // 20 characters
    double fee;       // up to 999.99

    // Validation helper methods
    static bool validateCode(const std::string& code);
    static bool validateFee(double fee);

public:
    // Default constructor
    Service();
    
    // Constructor
    Service(const std::string& code, const std::string& name, double fee);

    // Set fee
    void setFee(double newFee);

    // Getters
    std::string getCode() const { return code; }
    std::string getName() const { return name; }
    double getFee() const { return fee; }

    // File I/O
    void saveToFile(const std::string& filename) const;
    static std::vector<Service> loadFromFile(const std::string& filename);
};

#endif // SERVICE_H
