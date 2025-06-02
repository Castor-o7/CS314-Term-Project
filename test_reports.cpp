#include "ReportGenerator.h"
#include "Member.h"
#include "Provider.h"
#include "Service.h"
#include <iostream>

// this cpp serves as a test to verify the functionality of the ChocAn Report Generation System
int main() {
    try {
        std::cout << "=== ChocAn Report Generation System Test ===" << std::endl;
        
        // Create report generator
        ReportGenerator reportGen;
        
        // Create test data
        Member member1("John Doe", "123456789", "123 Main St", "Springfield", "IL", "62704", false);
        Member member2("Jane Smith", "987654321", "456 Oak Ave", "Springfield", "IL", "62701", false);
        Member member3("Bob Johnson", "555666777", "789 Pine St", "Springfield", "IL", "62702", false);
        
        Provider provider1("Dr. Sarah Wilson", "111222333", "100 Medical Dr", "Springfield", "IL", "62705");
        Provider provider2("Dr. Mike Brown", "444555666", "200 Health St", "Springfield", "IL", "62706");
        
        Service service1("598470", "Dietitian Session", 75.00);
        Service service2("883948", "Aerobics Session", 50.00);
        Service service3("123456", "Consultation", 100.00);
        
        // Add data to report generator
        reportGen.addMember(member1);
        reportGen.addMember(member2);
        reportGen.addMember(member3);
        reportGen.addProvider(provider1);
        reportGen.addProvider(provider2);
        reportGen.addService(service1);
        reportGen.addService(service2);
        reportGen.addService(service3);
        
        std::cout << "\nTest data created and loaded." << std::endl;
        
        // Save test data to files
        member1.saveToFile("members.csv");
        member2.saveToFile("members.csv");
        member3.saveToFile("members.csv");
        provider1.saveToFile("providers.csv");
        provider2.saveToFile("providers.csv");
        service1.saveToFile("services.csv");
        service2.saveToFile("services.csv");
        service3.saveToFile("services.csv");
        
        // Add some service records
        std::cout << "\nAdding service records..." << std::endl;
        reportGen.addServiceRecord("03-15-2025", "111222333", "123456789", "598470", "Initial consultation");
        reportGen.addServiceRecord("03-16-2025", "444555666", "987654321", "883948", "First aerobics session");
        reportGen.addServiceRecord("03-17-2025", "111222333", "123456789", "123456", "Follow-up consultation");
        reportGen.addServiceRecord("03-18-2025", "111222333", "555666777", "598470", "Diet planning session");
        reportGen.addServiceRecord("03-19-2025", "444555666", "987654321", "883948", "Second aerobics session");
        
        // Save service records
        reportGen.saveServiceRecords("service_records.csv");
        
        std::cout << "\n=== Generating Reports ===" << std::endl;
        
        // Generate individual member reports
        std::cout << "\nGenerating member reports..." << std::endl;
        reportGen.generateMemberReport("123456789");
        reportGen.generateMemberReport("987654321");
        reportGen.generateMemberReport("555666777");
        
        // Generate individual provider reports
        std::cout << "\nGenerating provider reports..." << std::endl;
        reportGen.generateProviderReport("111222333");
        reportGen.generateProviderReport("444555666");
        
        // Generate summary report
        std::cout << "\nGenerating summary report..." << std::endl;
        reportGen.generateSummaryReport();
        
        // Generate EFT report, GIMME DA MONIES
        std::cout << "\nGenerating EFT report..." << std::endl;
        reportGen.generateEFTReport();
        
        // Generate provider directory
        std::cout << "\nGenerating provider directory..." << std::endl;
        reportGen.generateProviderDirectory();
        
        // Generate all weekly reports at once, this is a requirement D'OH
        std::cout << "\n=== Testing Weekly Report Generation ===" << std::endl;
        reportGen.generateWeeklyReports();
        
        std::cout << "\n=== Testing Member Card Validation ===" << std::endl;
        std::cout << "Validating member 123456789: " << reportGen.validateMemberCard("123456789") << std::endl;
        std::cout << "Validating non-existent member 999999999: " << reportGen.validateMemberCard("999999999") << std::endl;
        
        // Test suspension. you been bad. HERE'S THE BANHAMMER
        member1.suspend();
        reportGen.updateMember("123456789", member1);
        std::cout << "Validating suspended member 123456789: " << reportGen.validateMemberCard("123456789") << std::endl;
        
        // Test reinstatement, ok welcum backkk
        member1.reinstate();
        reportGen.updateMember("123456789", member1);
        std::cout << "Validating reinstated member 123456789: " << reportGen.validateMemberCard("123456789") << std::endl;
        
        std::cout << "\n=== All tests completed successfully! ===" << std::endl;
        std::cout << "Check the generated .txt files for the reports." << std::endl;
        //this is a catch all for any exceptions that may occur during the test... this could be improvded?
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
