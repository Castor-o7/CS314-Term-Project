#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept>

class Member {
private:
    // Static map to store member numbers and their validation status
    static std::unordered_map<std::string, bool> memberValidationMap;

    // Member properties
    std::string name;          // 25 characters
    std::string number;        // 9 digits
    std::string streetAddress; // 25 characters
    std::string city;          // 14 characters
    std::string state;         // 2 characters
    std::string zipCode;       // 5 digits
    bool isSuspended;

    // Validation helper methods
    static bool validateNumber(const std::string& number) {
        return number.length() == 9 && std::all_of(number.begin(), number.end(), ::isdigit);
    }

    static bool validateState(const std::string& state) {
        return state.length() == 2 && std::all_of(state.begin(), state.end(), ::isalpha);
    }

    static bool validateZipCode(const std::string& zipCode) {
        return zipCode.length() == 5 && std::all_of(zipCode.begin(), zipCode.end(), ::isdigit);
    }

public:
    // Constructor
    Member(const std::string& name, const std::string& number, const std::string& streetAddress,
           const std::string& city, const std::string& state, const std::string& zipCode, bool isSuspended)
        : name(name), streetAddress(streetAddress), city(city), state(state), zipCode(zipCode), isSuspended(isSuspended) {
        if (!validateNumber(number)) {
            throw std::invalid_argument("Number must be exactly 9 digits.");
        }
        if (!validateState(state)) {
            throw std::invalid_argument("State must be exactly 2 characters.");
        }
        if (!validateZipCode(zipCode)) {
            throw std::invalid_argument("ZipCode must be exactly 5 digits.");
        }
        if (memberValidationMap.find(number) == memberValidationMap.end()) {
            throw std::invalid_argument("Member number is not registered in the system.");
        }

        this->number = number;
        memberValidationMap[number] = !isSuspended; // Update validation map
    }

    // Update member details
    void updateDetails(const std::string& streetAddress, const std::string& city, const std::string& state, const std::string& zipCode) {
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

    // Suspend the member
    void suspend() {
        isSuspended = true;
        memberValidationMap[number] = false; // Update validation map
    }

    // Reinstate the member
    void reinstate() {
        isSuspended = false;
        memberValidationMap[number] = true; // Update validation map
    }

    // Static method to register a new member number
    static void registerMemberNumber(const std::string& number) {
        if (!validateNumber(number)) {
            throw std::invalid_argument("Number must be exactly 9 digits.");
        }
        if (memberValidationMap.find(number) == memberValidationMap.end()) {
            memberValidationMap[number] = true; // Default to valid
        } else {
            throw std::invalid_argument("Member number already exists.");
        }
    }

    // Static method to validate a member number
    static std::string validateMemberNumber(const std::string& number) {
        if (memberValidationMap.find(number) != memberValidationMap.end()) {
            return memberValidationMap[number] ? "Validated" : "Member suspended";
        } else {
            return "Invalid member number";
        }
    }
};

