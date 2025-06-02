#include "ReportGenerator.h"
#include "ProviderTerminal.h"
#include "ManagerTerminal.h"
#include "Member.h"
#include "Provider.h"
#include "Service.h"
#include <iostream>
#include <iomanip>

//description: Main function to run the ChocAn Data Processing System this is the menuuuuu
//input: none
//output: prints a menu to the terminal
void displayMainMenu() {
    std::cout << "\n===================================" << std::endl;
    std::cout << "     ChocAn Data Processing System" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << "1. Provider Terminal" << std::endl;
    std::cout << "2. Manager Terminal" << std::endl;
    std::cout << "3. Run System Demo" << std::endl;
    std::cout << "4. Load Test Data" << std::endl;
    std::cout << "5. Exit System" << std::endl;
}

// description: this will load the data from the database with debugging information
// input: ReportGenerator object
// output: loads existing data from CSV files or creates test data
void loadExistingData(ReportGenerator& reportGen) {
    std::cout << "\n=== Loading Existing Data from CSV Files ===" << std::endl;
    
    // Try to load existing data files
    try {
        reportGen.loadMembers("members.csv");
    } catch (const std::exception& e) {
        std::cout << "Note: No existing members.csv file found." << std::endl;
    }
    
    try {
        reportGen.loadProviders("providers.csv");
    } catch (const std::exception& e) {
        std::cout << "Note: No existing providers.csv file found." << std::endl;
    }
    
    try {
        reportGen.loadServices("services.csv");
    } catch (const std::exception& e) {
        std::cout << "Note: No existing services.csv file found." << std::endl;
    }
    
    try {
        reportGen.loadServiceRecords("service_records.csv");
    } catch (const std::exception& e) {
        std::cout << "Note: No existing service_records.csv file found." << std::endl;
    }
    
    std::cout << "Data loading completed." << std::endl;
}

// description: this will load test data into the system without debugging information
// input: ReportGenerator object
// output: populates the system with predefined test members, providers, services, and service records
void loadTestData(ReportGenerator& reportGen) {
    std::cout << "\n=== Loading Test Data ===" << std::endl;
    
    // Create test members
    Member member1("John Doe", "123456789", "123 Main St", "Springfield", "IL", "62704", false);
    Member member2("Jane Smith", "987654321", "456 Oak Ave", "Springfield", "IL", "62701", false);
    Member member3("Bob Johnson", "555666777", "789 Pine St", "Springfield", "IL", "62702", false);
    Member member4("Alice Brown", "111222333", "321 Elm Dr", "Springfield", "IL", "62703", true); // Suspended
    
    // Create test providers
    Provider provider1("Dr. Sarah Wilson", "111222333", "100 Medical Dr", "Springfield", "IL", "62705");
    Provider provider2("Dr. Mike Brown", "444555666", "200 Health St", "Springfield", "IL", "62706");
    Provider provider3("Dr. Lisa Green", "777888999", "300 Wellness Ave", "Springfield", "IL", "62707");
    
    // Create test services
    Service service1("598470", "Dietitian Session", 75.00);
    Service service2("883948", "Aerobics Session", 50.00);
    Service service3("123456", "Consultation", 100.00);
    Service service4("456789", "Physical Therapy", 85.00);
    Service service5("789012", "Nutrition Counseling", 60.00);
    
    // Add data to report generator
    reportGen.addMember(member1);
    reportGen.addMember(member2);
    reportGen.addMember(member3);
    reportGen.addMember(member4);
    
    reportGen.addProvider(provider1);
    reportGen.addProvider(provider2);
    reportGen.addProvider(provider3);
    
    reportGen.addService(service1);
    reportGen.addService(service2);
    reportGen.addService(service3);
    reportGen.addService(service4);
    reportGen.addService(service5);
    
    // Add some service records for the current week
    reportGen.addServiceRecord("05-26-2025", "111222333", "123456789", "598470", "Initial consultation and diet planning");
    reportGen.addServiceRecord("05-26-2025", "444555666", "987654321", "883948", "First aerobics session - beginner level");
    reportGen.addServiceRecord("05-27-2025", "111222333", "123456789", "123456", "Follow-up consultation");
    reportGen.addServiceRecord("05-27-2025", "777888999", "555666777", "456789", "Physical therapy assessment");
    reportGen.addServiceRecord("05-27-2025", "444555666", "987654321", "789012", "Nutrition counseling session");
    
    std::cout << "Test data loaded successfully!" << std::endl;
    std::cout << "- 4 members (including 1 suspended)" << std::endl;
    std::cout << "- 3 providers" << std::endl;
    std::cout << "- 5 services" << std::endl;
    std::cout << "- 5 service records" << std::endl;
}


// description: this will run a demonstration of the ChocAn system
// input: ReportGenerator object
// output: simulates member validation, service billing, and report generation
void runSystemDemo(ReportGenerator& reportGen) {
    std::cout << "\n=== ChocAn System Demonstration ===" << std::endl;
    
    // Demo member validation
    std::cout << "\n--- Member Validation Demo ---" << std::endl;
    std::cout << "Testing member validation scenarios:" << std::endl;
    
    std::cout << "Validating active member 123456789: " << reportGen.validateMemberCard("123456789") << std::endl;
    std::cout << "Validating suspended member 111222333: " << reportGen.validateMemberCard("111222333") << std::endl;
    std::cout << "Validating invalid member 999999999: " << reportGen.validateMemberCard("999999999") << std::endl;
    
    // Demo service billing workflow
    std::cout << "\n--- Service Billing Workflow Demo ---" << std::endl;
    std::cout << "Simulating provider service billing process..." << std::endl;
    
    std::cout << "\n1. Member card validation: " << reportGen.validateMemberCard("987654321") << std::endl;
    std::cout << "2. Service date: 05-27-2025" << std::endl;
    std::cout << "3. Service code: 883948" << std::endl;
    std::cout << "4. Service name: Aerobics Session" << std::endl;
    std::cout << "5. Service fee: $50.00" << std::endl;
    std::cout << "6. Creating service record..." << std::endl;
    
    reportGen.addServiceRecord("05-27-2025", "444555666", "987654321", "883948", "Demo billing session");
    std::cout << "Service record created successfully!" << std::endl;
    
    // Demo report generation
    std::cout << "\n--- Report Generation Demo ---" << std::endl;
    std::cout << "Generating sample reports..." << std::endl;
    
    reportGen.generateMemberReport("123456789");
    std::cout << "✓ Member report generated" << std::endl;
    
    reportGen.generateProviderReport("111222333");
    std::cout << "✓ Provider report generated" << std::endl;
    
    reportGen.generateProviderDirectory();
    std::cout << "✓ Provider directory generated" << std::endl;
    
    reportGen.generateSummaryReport();
    std::cout << "✓ Summary report generated" << std::endl;
    
    reportGen.generateEFTReport();
    std::cout << "✓ EFT report generated" << std::endl;
    
    std::cout << "\nDemo completed! Check the generated .txt files for report contents." << std::endl;
}

// Finally here is the main function that initializes the system and runs the menu loop
int main() {
    std::cout << "Starting ChocAn Data Processing System..." << std::endl;
    
    // Initialize the report generator (main data processing component)
    ReportGenerator reportGen;
    
    // Load existing data from CSV files
    loadExistingData(reportGen);
    
    // Initialize terminal interfaces
    ProviderTerminal providerTerminal(&reportGen);
    ManagerTerminal managerTerminal(&reportGen);
    
    std::cout << "System initialized successfully." << std::endl;
    
    while (true) {
        displayMainMenu();
        
        int choice;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline from buffer
        
        switch (choice) {
            case 1:
                std::cout << "\nLaunching Provider Terminal..." << std::endl;
                providerTerminal.simulateKeyboardInput();
                providerTerminal.run();
                break;
                
            case 2:
                std::cout << "\nLaunching Manager Terminal..." << std::endl;
                managerTerminal.simulateKeyboardInput();
                managerTerminal.run();
                break;
                
            case 3:
                runSystemDemo(reportGen);
                break;
                
            case 4:
                loadTestData(reportGen);
                break;
                
            case 5:
                std::cout << "\nShutting down ChocAn Data Processing System..." << std::endl;
                std::cout << "Thank you for using ChocAn!" << std::endl;
                return 0;
                
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
        
        // Pause before showing menu again
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    return 0;
}
