#include "ManagerTerminal.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

// Constructor, again don't forget this one lol
ManagerTerminal::ManagerTerminal(ReportGenerator* reportGenerator) 
    : reportGen(reportGenerator) {
}

//description: Main terminal interface for manager operations
//input: none
//output: displays the main menu and handles user input for various management tasks
void ManagerTerminal::run() {
    std::cout << "=== ChocAn Manager Terminal ===" << std::endl;
    std::cout << "Manager terminal ready for operation." << std::endl;
    
    while (true) {
        displayMainMenu();
        
        int choice;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline from buffer
        
        switch (choice) {
            case 1:
                memberManagementMenu();
                break;
            case 2:
                providerManagementMenu();
                break;
            case 3:
                reportsMenu();
                break;
            case 4:
                std::cout << "Logging out of Manager Terminal. Goodbye!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

//description: Displays the main menu for the manager terminal
//input: none
//output: prints the main menu options to the console
void ManagerTerminal::displayMainMenu() {
    std::cout << "\n=== Manager Terminal Menu ===" << std::endl;
    std::cout << "1. Member Management" << std::endl;
    std::cout << "2. Provider Management" << std::endl;
    std::cout << "3. Reports" << std::endl;
    std::cout << "4. Logout" << std::endl;
}

//description: Displays the member management menu and handles user input for member operations
//input: none
//output: prints the member management options and processes user choices
void ManagerTerminal::memberManagementMenu() {
    while (true) {
        std::cout << "\n=== Member Management ===" << std::endl;
        std::cout << "1. Add New Member" << std::endl;
        std::cout << "2. Delete Member" << std::endl;
        std::cout << "3. Update Member" << std::endl;
        std::cout << "4. View Member" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;
        
        int choice;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                addMember();
                break;
            case 2:
                deleteMember();
                break;
            case 3:
                updateMember();
                break;
            case 4:
                viewMember();
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

//description: Displays the provider management menu and handles user input for provider operations
//input: none
//output: prints the provider management options and processes user choices
void ManagerTerminal::providerManagementMenu() {
    while (true) {
        std::cout << "\n=== Provider Management ===" << std::endl;
        std::cout << "1. Add New Provider" << std::endl;
        std::cout << "2. Delete Provider" << std::endl;
        std::cout << "3. Update Provider" << std::endl;
        std::cout << "4. View Provider" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;
        
        int choice;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                addProvider();
                break;
            case 2:
                deleteProvider();
                break;
            case 3:
                updateProvider();
                break;
            case 4:
                viewProvider();
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

//description: Displays the reports menu and handles user input for report generation
//input: none
//output: prints the report generation options and processes user choices
void ManagerTerminal::reportsMenu() {
    while (true) {
        std::cout << "\n=== Reports Menu ===" << std::endl;
        std::cout << "1. Generate Individual Member Report" << std::endl;
        std::cout << "2. Generate Individual Provider Report" << std::endl;
        std::cout << "3. Generate Summary Report" << std::endl;
        std::cout << "4. Generate EFT Report" << std::endl;
        std::cout << "5. Generate Provider Directory" << std::endl;
        std::cout << "6. Generate All Weekly Reports" << std::endl;
        std::cout << "7. Back to Main Menu" << std::endl;
        
        int choice;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                generateIndividualMemberReport();
                break;
            case 2:
                generateIndividualProviderReport();
                break;
            case 3:
                generateSummaryReport();
                break;
            case 4:
                generateEFTReport();
                break;
            case 5:
                generateProviderDirectory();
                break;
            case 6:
                generateAllWeeklyReports();
                break;
            case 7:
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

// Member Management Methods, these are fairly self explanatory so I have not left many comments
void ManagerTerminal::addMember() {
    std::cout << "\n=== Add New Member ===" << std::endl;
    
    std::string name, number, streetAddress, city, state, zipCode;
    
    std::cout << "Enter member name (max 25 characters): ";
    std::getline(std::cin, name);
    if (name.length() > 25) {
        name = name.substr(0, 25);
        std::cout << "Name truncated to 25 characters." << std::endl;
    }
    
    std::cout << "Enter member number (9 digits): ";
    std::getline(std::cin, number);
    if (!validateMemberNumber(number)) {
        std::cout << "Invalid member number. Must be exactly 9 digits." << std::endl;
        return;
    }
    
    std::cout << "Enter street address (max 25 characters): ";
    std::getline(std::cin, streetAddress);
    if (streetAddress.length() > 25) {
        streetAddress = streetAddress.substr(0, 25);
        std::cout << "Street address truncated to 25 characters." << std::endl;
    }
    
    std::cout << "Enter city (max 14 characters): ";
    std::getline(std::cin, city);
    if (city.length() > 14) {
        city = city.substr(0, 14);
        std::cout << "City truncated to 14 characters." << std::endl;
    }
    
    std::cout << "Enter state (2 characters): ";
    std::getline(std::cin, state);
    if (!validateState(state)) {
        std::cout << "Invalid state. Must be exactly 2 characters." << std::endl;
        return;
    }
    
    std::cout << "Enter zip code (5 digits): ";
    std::getline(std::cin, zipCode);
    if (!validateZipCode(zipCode)) {
        std::cout << "Invalid zip code. Must be exactly 5 digits." << std::endl;
        return;
    }
    
    try {
        Member newMember(name, number, streetAddress, city, state, zipCode, false);
        reportGen->addMember(newMember);
        std::cout << "Member added successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error adding member: " << e.what() << std::endl;
    }
}

void ManagerTerminal::deleteMember() {
    std::cout << "\n=== Delete Member ===" << std::endl;
    
    std::string memberNumber;
    std::cout << "Enter member number to delete (9 digits): ";
    std::getline(std::cin, memberNumber);
    
    if (!validateMemberNumber(memberNumber)) {
        std::cout << "Invalid member number format." << std::endl;
        return;
    }
    
    std::cout << "Are you sure you want to delete member " << memberNumber << "? (y/n): ";
    char confirmation;
    std::cin >> confirmation;
    std::cin.ignore();
    
    if (confirmation == 'y' || confirmation == 'Y') {
        // Note: ReportGenerator doesn't have a delete method implemented
        // In a real system, this would remove the member from the database
        std::cout << "Member deletion functionality would be implemented here." << std::endl;
        std::cout << "Member " << memberNumber << " marked for deletion." << std::endl;
    } else {
        std::cout << "Deletion cancelled." << std::endl;
    }
}

void ManagerTerminal::updateMember() {
    std::cout << "\n=== Update Member ===" << std::endl;
    
    std::string memberNumber;
    std::cout << "Enter member number to update (9 digits): ";
    std::getline(std::cin, memberNumber);
    
    if (!validateMemberNumber(memberNumber)) {
        std::cout << "Invalid member number format." << std::endl;
        return;
    }
    
    // Check if member exists
    std::string validationResult = reportGen->validateMemberCard(memberNumber);
    if (validationResult == "Invalid Member Number") {
        std::cout << "Member not found." << std::endl;
        return;
    }
    
    std::cout << "Select field to update:" << std::endl;
    std::cout << "1. Street Address" << std::endl;
    std::cout << "2. City" << std::endl;
    std::cout << "3. State" << std::endl;
    std::cout << "4. Zip Code" << std::endl;
    std::cout << "5. Suspend/Reinstate Member" << std::endl;
    
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    
    switch (choice) {
        case 5: {
            std::cout << "1. Suspend Member" << std::endl;
            std::cout << "2. Reinstate Member" << std::endl;
            int suspendChoice;
            std::cin >> suspendChoice;
            std::cin.ignore();
            
            if (suspendChoice == 1) {
                std::cout << "Member " << memberNumber << " suspended." << std::endl;
            } else if (suspendChoice == 2) {
                std::cout << "Member " << memberNumber << " reinstated." << std::endl;
            }
            break;
        }
        default:
            std::cout << "Update functionality would be implemented here." << std::endl;
            break;
    }
}

void ManagerTerminal::viewMember() {
    std::cout << "\n=== View Member ===" << std::endl;
    
    std::string memberNumber;
    std::cout << "Enter member number (9 digits): ";
    std::getline(std::cin, memberNumber);
    
    if (!validateMemberNumber(memberNumber)) {
        std::cout << "Invalid member number format." << std::endl;
        return;
    }
    
    std::string validationResult = reportGen->validateMemberCard(memberNumber);
    std::cout << "Member Status: " << validationResult << std::endl;
    
    if (validationResult != "Invalid Member Number") {
        std::cout << "Member details would be displayed here." << std::endl;
    }
}

// Provider Management Methods
void ManagerTerminal::addProvider() {
    std::cout << "\n=== Add New Provider ===" << std::endl;
    
    std::string name, number, streetAddress, city, state, zipCode;
    
    std::cout << "Enter provider name (max 25 characters): ";
    std::getline(std::cin, name);
    if (name.length() > 25) {
        name = name.substr(0, 25);
        std::cout << "Name truncated to 25 characters." << std::endl;
    }
    
    std::cout << "Enter provider number (9 digits): ";
    std::getline(std::cin, number);
    if (!validateProviderNumber(number)) {
        std::cout << "Invalid provider number. Must be exactly 9 digits." << std::endl;
        return;
    }
    
    std::cout << "Enter street address (max 25 characters): ";
    std::getline(std::cin, streetAddress);
    if (streetAddress.length() > 25) {
        streetAddress = streetAddress.substr(0, 25);
        std::cout << "Street address truncated to 25 characters." << std::endl;
    }
    
    std::cout << "Enter city (max 14 characters): ";
    std::getline(std::cin, city);
    if (city.length() > 14) {
        city = city.substr(0, 14);
        std::cout << "City truncated to 14 characters." << std::endl;
    }
    
    std::cout << "Enter state (2 characters): ";
    std::getline(std::cin, state);
    if (!validateState(state)) {
        std::cout << "Invalid state. Must be exactly 2 characters." << std::endl;
        return;
    }
    
    std::cout << "Enter zip code (5 digits): ";
    std::getline(std::cin, zipCode);
    if (!validateZipCode(zipCode)) {
        std::cout << "Invalid zip code. Must be exactly 5 digits." << std::endl;
        return;
    }
    
    try {
        Provider newProvider(name, number, streetAddress, city, state, zipCode);
        reportGen->addProvider(newProvider);
        std::cout << "Provider added successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error adding provider: " << e.what() << std::endl;
    }
}

void ManagerTerminal::deleteProvider() {
    std::cout << "\n=== Delete Provider ===" << std::endl;
    
    std::string providerNumber;
    std::cout << "Enter provider number to delete (9 digits): ";
    std::getline(std::cin, providerNumber);
    
    if (!validateProviderNumber(providerNumber)) {
        std::cout << "Invalid provider number format." << std::endl;
        return;
    }
    
    std::cout << "Are you sure you want to delete provider " << providerNumber << "? (y/n): ";
    char confirmation;
    std::cin >> confirmation;
    std::cin.ignore();
    
    if (confirmation == 'y' || confirmation == 'Y') {
        std::cout << "Provider deletion functionality would be implemented here." << std::endl;
        std::cout << "Provider " << providerNumber << " marked for deletion." << std::endl;
    } else {
        std::cout << "Deletion cancelled." << std::endl;
    }
}

void ManagerTerminal::updateProvider() {
    std::cout << "\n=== Update Provider ===" << std::endl;
    std::cout << "Provider update functionality would be implemented here." << std::endl;
}

void ManagerTerminal::viewProvider() {
    std::cout << "\n=== View Provider ===" << std::endl;
    std::cout << "Provider view functionality would be implemented here." << std::endl;
}

// Report Generation Methods
void ManagerTerminal::generateIndividualMemberReport() {
    std::cout << "\n=== Generate Individual Member Report ===" << std::endl;
    
    std::string memberNumber;
    std::cout << "Enter member number (9 digits): ";
    std::getline(std::cin, memberNumber);
    
    if (!validateMemberNumber(memberNumber)) {
        std::cout << "Invalid member number format." << std::endl;
        return;
    }
    
    std::cout << "Generating member report..." << std::endl;
    reportGen->generateMemberReport(memberNumber);
    std::cout << "Member report generated successfully." << std::endl;
}

void ManagerTerminal::generateIndividualProviderReport() {
    std::cout << "\n=== Generate Individual Provider Report ===" << std::endl;
    
    std::string providerNumber;
    std::cout << "Enter provider number (9 digits): ";
    std::getline(std::cin, providerNumber);
    
    if (!validateProviderNumber(providerNumber)) {
        std::cout << "Invalid provider number format." << std::endl;
        return;
    }
    
    std::cout << "Generating provider report..." << std::endl;
    reportGen->generateProviderReport(providerNumber);
    std::cout << "Provider report generated successfully." << std::endl;
}

void ManagerTerminal::generateSummaryReport() {
    std::cout << "\n=== Generate Summary Report ===" << std::endl;
    std::cout << "Generating accounts payable summary report..." << std::endl;
    reportGen->generateSummaryReport();
    std::cout << "Summary report generated successfully." << std::endl;
}

void ManagerTerminal::generateEFTReport() {
    std::cout << "\n=== Generate EFT Report ===" << std::endl;
    std::cout << "Generating Electronic Funds Transfer data..." << std::endl;
    reportGen->generateEFTReport();
    std::cout << "EFT report generated successfully." << std::endl;
}

void ManagerTerminal::generateProviderDirectory() {
    std::cout << "\n=== Generate Provider Directory ===" << std::endl;
    std::cout << "Generating provider directory..." << std::endl;
    reportGen->generateProviderDirectory();
    std::cout << "Provider directory generated successfully." << std::endl;
}

void ManagerTerminal::generateAllWeeklyReports() {
    std::cout << "\n=== Generate All Weekly Reports ===" << std::endl;
    std::cout << "Running main accounting procedure..." << std::endl;
    std::cout << "This simulates the Friday midnight batch process." << std::endl;
    reportGen->generateWeeklyReports();
    std::cout << "All weekly reports generated successfully." << std::endl;
}

// Utility methods
bool ManagerTerminal::validateMemberNumber(const std::string& number) {
    return number.length() == 9 && 
           std::all_of(number.begin(), number.end(), ::isdigit);
}

bool ManagerTerminal::validateProviderNumber(const std::string& number) {
    return number.length() == 9 && 
           std::all_of(number.begin(), number.end(), ::isdigit);
}

bool ManagerTerminal::validateState(const std::string& state) {
    return state.length() == 2 && 
           std::all_of(state.begin(), state.end(), ::isalpha);
}

bool ManagerTerminal::validateZipCode(const std::string& zipCode) {
    return zipCode.length() == 5 && 
           std::all_of(zipCode.begin(), zipCode.end(), ::isdigit);
}

// Simulation methods
void ManagerTerminal::simulateKeyboardInput() {
    std::cout << "\n[SIMULATION] Manager terminal keyboard input mode activated." << std::endl;
    std::cout << "All manager terminal operations will be simulated via keyboard input." << std::endl;
    std::cout << "All output will appear on this screen." << std::endl;
}
