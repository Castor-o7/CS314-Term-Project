#include "ProviderTerminal.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>

// Constructor
ProviderTerminal::ProviderTerminal(ReportGenerator* reportGenerator) 
    : reportGen(reportGenerator), currentProviderNumber("") {
}

// Main terminal interface
void ProviderTerminal::run() {
    std::cout << "=== ChocAn Provider Terminal ===" << std::endl;
    std::cout << "Terminal ready for operation." << std::endl;
    
    loginProvider();
    
    while (true) {
        displayMenu();
        
        int choice;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline from buffer
        
        switch (choice) {
            case 1:
                memberValidation();
                break;
            case 2:
                serviceBilling();
                break;
            case 3:
                requestProviderDirectory();
                break;
            case 4:
                std::cout << "Logging out. Thank you for using ChocAn!" << std::endl;
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}

void ProviderTerminal::loginProvider() {
    std::cout << "\n=== Provider Login ===" << std::endl;
    std::cout << "Please enter your provider number (9 digits): ";
    std::getline(std::cin, currentProviderNumber);
    
    // Validate provider number format
    if (currentProviderNumber.length() != 9 || 
        !std::all_of(currentProviderNumber.begin(), currentProviderNumber.end(), ::isdigit)) {
        std::cout << "Invalid provider number format. Must be 9 digits." << std::endl;
        loginProvider();
        return;
    }
    
    // TODO: In a real system, we would validate the provider exists
    // For simulation, we'll accept any valid format
    std::cout << "Provider " << currentProviderNumber << " logged in successfully." << std::endl;
}

void ProviderTerminal::displayMenu() {
    std::cout << "\n=== Provider Terminal Menu ===" << std::endl;
    std::cout << "1. Member Validation" << std::endl;
    std::cout << "2. Service Billing" << std::endl;
    std::cout << "3. Request Provider Directory" << std::endl;
    std::cout << "4. Logout" << std::endl;
}

void ProviderTerminal::memberValidation() {
    std::cout << "\n=== Member Validation ===" << std::endl;
    std::cout << "Please swipe member card or enter member number manually:" << std::endl;
    std::cout << "Member number (9 digits): ";
    
    std::string memberNumber;
    std::getline(std::cin, memberNumber);
    
    // Validate member number format
    if (memberNumber.length() != 9 || 
        !std::all_of(memberNumber.begin(), memberNumber.end(), ::isdigit)) {
        std::cout << "Invalid Number" << std::endl;
        return;
    }
    
    // Validate member with ChocAn Data Center
    std::cout << "Validating member with ChocAn Data Center..." << std::endl;
    std::string validationResult = reportGen->validateMemberCard(memberNumber);
    std::cout << validationResult << std::endl;
}

void ProviderTerminal::serviceBilling() {
    std::cout << "\n=== Service Billing ===" << std::endl;
    
    // Step 1: Member validation
    std::cout << "Please swipe member card or enter member number:" << std::endl;
    std::cout << "Member number (9 digits): ";
    
    std::string memberNumber;
    std::getline(std::cin, memberNumber);
    
    // Validate member number format
    if (memberNumber.length() != 9 || 
        !std::all_of(memberNumber.begin(), memberNumber.end(), ::isdigit)) {
        std::cout << "Invalid Number" << std::endl;
        return;
    }
    
    // Validate member
    std::string validationResult = reportGen->validateMemberCard(memberNumber);
    std::cout << validationResult << std::endl;
    
    if (validationResult != "Validated") {
        std::cout << "Cannot proceed with billing. Member validation failed." << std::endl;
        return;
    }
    
    // Step 2: Date of service
    std::cout << "\nEnter date service was provided (MM-DD-YYYY): ";
    std::string serviceDate;
    std::getline(std::cin, serviceDate);
    
    if (!validateDateFormat(serviceDate)) {
        std::cout << "Invalid date format. Please use MM-DD-YYYY." << std::endl;
        return;
    }
    
    // Step 3: Service code entry
    std::cout << "\nRefer to Provider Directory for service codes." << std::endl;
    std::cout << "Enter service code (6 digits): ";
    std::string serviceCode;
    std::getline(std::cin, serviceCode);
    
    if (!validateServiceCode(serviceCode)) {
        std::cout << "Invalid service code format. Must be 6 digits." << std::endl;
        return;
    }
    
    // Step 4: Service verification
    // In a real system, we would look up the service in our database
    // For simulation, we'll use our test services that are hardcoded in the reportgenny. Is this a known issue?
    std::cout << "\nLooking up service..." << std::endl;
    
    // For demo purposes, simulate service lookup. We love a good demo!!~
    std::string serviceName = "Unknown Service";
    double serviceFee = 0.0;
    
    if (serviceCode == "598470") {
        serviceName = "Dietitian Session";
        serviceFee = 75.00;
    } else if (serviceCode == "883948") {
        serviceName = "Aerobics Session";
        serviceFee = 50.00;
    } else if (serviceCode == "123456") {
        serviceName = "Consultation";
        serviceFee = 100.00;
    } else {
        std::cout << "Service code not found in directory." << std::endl;
        return;
    }
    
    // confirm the service details with the provider with the current provideahhhh
    std::cout << "Service: " << serviceName << std::endl;
    std::cout << "Is this the correct service? (y/n): ";
    char confirmation;
    std::cin >> confirmation;
    std::cin.ignore();
    
    if (confirmation != 'y' && confirmation != 'Y') {
        std::cout << "Service billing cancelled." << std::endl;
        return;
    }
    
    // Step 5: Optional comments. GIMME DA COMMENTS MAN
    std::cout << "\nEnter comments (optional, max 100 characters): ";
    std::string comments;
    std::getline(std::cin, comments);
    
    if (comments.length() > 100) {
        comments = comments.substr(0, 100);
        std::cout << "Comments truncated to 100 characters." << std::endl;
    }
    
    // Step 6: Create service record
    std::cout << "\nCreating service record..." << std::endl;
    reportGen->addServiceRecord(serviceDate, currentProviderNumber, memberNumber, serviceCode, comments);
    
    // Step 7: Display fee
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Fee to be paid: $" << serviceFee << std::endl;
    std::cout << "Service record created successfully." << std::endl;
}

void ProviderTerminal::requestProviderDirectory() {
    std::cout << "\n=== Provider Directory Request ===" << std::endl;
    std::cout << "Generating Provider Directory..." << std::endl;
    
    reportGen->generateProviderDirectory();
    
    std::cout << "Provider Directory has been created as 'Provider_Directory.txt'" << std::endl;
    std::cout << "The directory contains an alphabetically ordered list of:" << std::endl;
    std::cout << "- Service names" << std::endl;
    std::cout << "- Service codes" << std::endl;
    std::cout << "- Service fees" << std::endl;
}

// Helper methods
std::string ProviderTerminal::getCurrentDateTime() {
    auto now = std::time(nullptr);
    auto* tm = std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::setfill('0') 
        << std::setw(2) << (tm->tm_mon + 1) << "-"
        << std::setw(2) << tm->tm_mday << "-"
        << (tm->tm_year + 1900) << " "
        << std::setw(2) << tm->tm_hour << ":"
        << std::setw(2) << tm->tm_min << ":"
        << std::setw(2) << tm->tm_sec;
    
    return oss.str();
}

bool ProviderTerminal::validateDateFormat(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    
    // Check if all other characters are digits
    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (!std::isdigit(date[i])) return false;
    }
    
    return true;
}

bool ProviderTerminal::validateServiceCode(const std::string& code) {
    return code.length() == 6 && 
           std::all_of(code.begin(), code.end(), ::isdigit);
}

// Simulation methods for testing
void ProviderTerminal::simulateCardSwipe(const std::string& memberNumber) {
    std::cout << "\n[SIMULATION] Card swiped: " << memberNumber << std::endl;
    std::string validationResult = reportGen->validateMemberCard(memberNumber);
    std::cout << validationResult << std::endl;
}

void ProviderTerminal::simulateKeyboardInput() {
    std::cout << "\n[SIMULATION] Keyboard input mode activated." << std::endl;
    std::cout << "All provider terminal data will be simulated via keyboard input." << std::endl;
    std::cout << "All output will appear on this screen." << std::endl;
}
