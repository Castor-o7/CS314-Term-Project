#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <unordered_map>
#include <vector>

class Member {
private:
    // Member properties
    std::string name;          // 25 characters
    std::string number;        // 9 digits
    std::string streetAddress; // 25 characters
    std::string city;          // 14 characters
    std::string state;         // 2 characters
    std::string zipCode;       // 5 digits
    bool isSuspended;

    // Validation helper methods
    static bool validateNumber(const std::string& number);
    static bool validateState(const std::string& state);
    static bool validateZipCode(const std::string& zipCode);

public:
    // Default constructor
    Member();
    
    // Constructor
    Member(const std::string& name, const std::string& number, const std::string& streetAddress,
           const std::string& city, const std::string& state, const std::string& zipCode, bool isSuspended);

    // Update member details
    void updateDetails(const std::string& streetAddress, const std::string& city, 
                      const std::string& state, const std::string& zipCode);

    // Suspend the member
    void suspend();

    // Reinstate the member
    void reinstate();

    // Getters
    std::string getName() const { return name; }
    std::string getNumber() const { return number; }
    std::string getStreetAddress() const { return streetAddress; }
    std::string getCity() const { return city; }
    std::string getState() const { return state; }
    std::string getZipCode() const { return zipCode; }
    bool getIsSuspended() const { return isSuspended; }

    // File I/O
    void saveToFile(const std::string& filename) const;
    static std::vector<Member> loadFromFile(const std::string& filename);
};

#endif // MEMBER_H
