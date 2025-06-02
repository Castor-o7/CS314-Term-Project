#include "Member.h"
#include "Provider.h"
#include "Service.h"
#include "ReportGenerator.h"
#include <iostream>

int main() {
    try {
        // Test Member class
        std::cout << "=== Testing Member Class ===" << std::endl;
        
        // Create report generator for validation
        ReportGenerator reportGen;
        
        // Create a new member
        Member member("John Doe", "123456789", "123 Main St", "Springfield", "IL", "62704", false);
        std::cout << "Created member: " << member.getName() << std::endl;
        
        // Add member to the system
        reportGen.addMember(member);
        
        // Validate member card
        std::cout << "Member 123456789: " << reportGen.validateMemberCard("123456789") << std::endl;
        std::cout << "Non-existent member: " << reportGen.validateMemberCard("987654321") << std::endl;
        
        // Suspend and reinstate
        member.suspend();
        reportGen.updateMember("123456789", member);
        std::cout << "After suspension: " << reportGen.validateMemberCard("123456789") << std::endl;
        
        member.reinstate();
        reportGen.updateMember("123456789", member);
        std::cout << "After reinstatement: " << reportGen.validateMemberCard("123456789") << std::endl;
        
        // Test Provider class
        std::cout << "\n=== Testing Provider Class ===" << std::endl;
        
        Provider provider("Dr. Smith", "555123456", "456 Oak Ave", "Springfield", "IL", "62701");
        std::cout << "Created provider: " << provider.getName() << std::endl;
        std::cout << "Provider number: " << provider.getNumber() << std::endl;
        
        // Test Service class
        std::cout << "\n=== Testing Service Class ===" << std::endl;
        
        Service service("598470", "Dietitian Session", 99.99);
        std::cout << "Created service: " << service.getName() << std::endl;
        std::cout << "Service code: " << service.getCode() << std::endl;
        std::cout << "Service fee: $" << service.getFee() << std::endl;
        
        // Test file I/O
        std::cout << "\n=== Testing File I/O ===" << std::endl;
        
        member.saveToFile("members.csv");
        provider.saveToFile("providers.csv");
        service.saveToFile("services.csv");
        std::cout << "Data saved to files." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
