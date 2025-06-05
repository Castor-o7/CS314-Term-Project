#include "Member.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>

// Default constructor
Member::Member() : name(""), number(""), streetAddress(""), city(""), state(""), zipCode(""), isSuspended(false) {
    // Empty default constructor for map compatibility. this is VERY important, I broke it for like two days because I kept forgetting this.
}

//description: Validation helper methods
//input: number, state, zipCode as strings
//output: bool indicating whether the input is valid
bool Member::validateNumber(const std::string& number) {
    return number.length() == 9 && std::all_of(number.begin(), number.end(), ::isdigit);
}

// description: Validate state format
// input: state as a string
// output: bool indicating whether the state is valid (exactly 2 alphabetic characters)
bool Member::validateState(const std::string& state) {
    return state.length() == 2 && std::all_of(state.begin(), state.end(), ::isalpha);
}

// description: Validate zip code format
// input: zipCode as a string
// output: bool indicating whether the zip code is valid (exactly 5 digits)
bool Member::validateZipCode(const std::string& zipCode) {
    return zipCode.length() == 5 && std::all_of(zipCode.begin(), zipCode.end(), ::isdigit);
}

// Constructor, initializes member details. Another one you realyy shouldn't forget lol
Member::Member(const std::string& name, const std::string& number, const std::string& streetAddress,
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

    this->number = number;
}

//description: Update member details
//input: streetAddress, city, state, zipCode as strings
//output: updates the member's address details
void Member::updateDetails(const std::string& streetAddress, const std::string& city, 
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

// YOU ARE (STOMP STOMP) SUSPENDEEEEEEDDDDD WOH WOHHHHH
void Member::suspend() {
    isSuspended = true;
}

// ok welcum back, you are no longer suspended
void Member::reinstate() {
    isSuspended = false;
}

//description: Save member details to a file
//input: filename as a string
//output: appends member details to the specified file
void Member::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::app);
    ofs << name << ',' << number << ',' << streetAddress << ',' << city << ',' << state << ',' << zipCode << ',' << isSuspended << '\n';
}

//description: Load member details from a file
//input: filename as a string
//output: returns a vector of Member objects loaded from the file
std::vector<Member> Member::loadFromFile(const std::string& filename) {
    std::vector<Member> members;
    std::ifstream ifs(filename);
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string name, number, streetAddress, city, state, zipCode, suspendedStr;
        std::getline(ss, name, ',');
        std::getline(ss, number, ',');
        std::getline(ss, streetAddress, ',');
        std::getline(ss, city, ',');
        std::getline(ss, state, ',');
        std::getline(ss, zipCode, ',');
        std::getline(ss, suspendedStr, ',');
        bool isSuspended = (suspendedStr == "1" || suspendedStr == "true");
        try {
            members.emplace_back(name, number, streetAddress, city, state, zipCode, isSuspended);
        } catch (...) { /* skip invalid lines */ }
    }
    return members;
}

