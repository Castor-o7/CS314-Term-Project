#ifndef PROVIDER_TERMINAL_H
#define PROVIDER_TERMINAL_H

#include "ReportGenerator.h"
#include "Member.h"
#include "Provider.h"
#include "Service.h"
#include <string>
#include <iostream>

class ProviderTerminal {
private:
    ReportGenerator* reportGen;
    std::string currentProviderNumber;
    
    // Helper methods
    void displayMenu();
    void memberValidation();
    void serviceBilling();
    void requestProviderDirectory();
    std::string getCurrentDateTime();
    std::string formatDate(const std::string& date);
    bool validateDateFormat(const std::string& date);
    bool validateServiceCode(const std::string& code);
    
public:
    // Constructor
    ProviderTerminal(ReportGenerator* reportGenerator);
    
    // Main interface methods
    void run();
    void loginProvider();
    void processServiceBilling();
    void handleMemberValidation();
    
    // Simulation methods for testing
    void simulateCardSwipe(const std::string& memberNumber);
    void simulateKeyboardInput();
};

#endif // PROVIDER_TERMINAL_H
