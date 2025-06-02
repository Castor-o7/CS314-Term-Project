#ifndef MANAGER_TERMINAL_H
#define MANAGER_TERMINAL_H

#include "ReportGenerator.h"
#include "Member.h"
#include "Provider.h"
#include "Service.h"
#include <string>
#include <iostream>

class ManagerTerminal {
private:
    ReportGenerator* reportGen;
    
    // Helper methods
    void displayMainMenu();
    void memberManagementMenu();
    void providerManagementMenu();
    void reportsMenu();
    
    // Member management
    void addMember();
    void deleteMember();
    void updateMember();
    void viewMember();
    
    // Provider management
    void addProvider();
    void deleteProvider();
    void updateProvider();
    void viewProvider();
    
    // Report generation
    void generateIndividualMemberReport();
    void generateIndividualProviderReport();
    void generateSummaryReport();
    void generateEFTReport();
    void generateProviderDirectory();
    void generateAllWeeklyReports();
    
    // Utility methods
    bool validateMemberNumber(const std::string& number);
    bool validateProviderNumber(const std::string& number);
    bool validateState(const std::string& state);
    bool validateZipCode(const std::string& zipCode);
    
public:
    // Constructor
    ManagerTerminal(ReportGenerator* reportGenerator);
    
    // Main interface
    void run();
    
    // Simulation methods
    void simulateKeyboardInput();
};

#endif // MANAGER_TERMINAL_H
