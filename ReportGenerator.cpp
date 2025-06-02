#include "ReportGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <set>

// Constructor
ReportGenerator::ReportGenerator() {
    // Initialize empty directories
}

// Helper method to get current date and time
std::string ReportGenerator::getCurrentDateTime() const {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%m-%d-%Y %H:%M:%S");
    return oss.str();
}

// Helper method to format currency
std::string ReportGenerator::formatCurrency(double amount) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << "$" << amount;
    return oss.str();
}

// Helper method to write content to file
void ReportGenerator::writeToFile(const std::string& filename, const std::string& content) const {
    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        ofs << content;
        ofs.close();
        std::cout << "Report written to: " << filename << std::endl;
    } else {
        std::cerr << "Error: Could not create file " << filename << std::endl;
    }
}

// Get services for a specific member
std::vector<ServiceRecord> ReportGenerator::getServicesForMember(const std::string& memberNumber) const {
    std::vector<ServiceRecord> memberServices;
    for (const auto& record : serviceRecords) {
        if (record.memberNumber == memberNumber) {
            memberServices.push_back(record);
        }
    }
    
    // Sort by service date
    std::sort(memberServices.begin(), memberServices.end(),
              [](const ServiceRecord& a, const ServiceRecord& b) {
                  return a.serviceDate < b.serviceDate;
              });
    
    return memberServices;
}

// Get services for a specific provider
std::vector<ServiceRecord> ReportGenerator::getServicesForProvider(const std::string& providerNumber) const {
    std::vector<ServiceRecord> providerServices;
    for (const auto& record : serviceRecords) {
        if (record.providerNumber == providerNumber) {
            providerServices.push_back(record);
        }
    }
    
    // Sort by date received (currentDateTime)
    std::sort(providerServices.begin(), providerServices.end(),
              [](const ServiceRecord& a, const ServiceRecord& b) {
                  return a.currentDateTime < b.currentDateTime;
              });
    
    return providerServices;
}

// Load members from file
void ReportGenerator::loadMembers(const std::string& filename) {
    auto members = Member::loadFromFile(filename);
    memberDirectory.clear();
    for (const auto& member : members) {
        memberDirectory[member.getNumber()] = member;
    }
    std::cout << "Loaded " << members.size() << " members from " << filename << std::endl;
}

// Load providers from file
void ReportGenerator::loadProviders(const std::string& filename) {
    auto providers = Provider::loadFromFile(filename);
    providerDirectory.clear();
    for (const auto& provider : providers) {
        providerDirectory[provider.getNumber()] = provider;
    }
    std::cout << "Loaded " << providers.size() << " providers from " << filename << std::endl;
}

// Load services from file
void ReportGenerator::loadServices(const std::string& filename) {
    auto services = Service::loadFromFile(filename);
    serviceDirectory.clear();
    for (const auto& service : services) {
        serviceDirectory[service.getCode()] = service;
    }
    std::cout << "Loaded " << services.size() << " services from " << filename << std::endl;
}

// Load service records from file
void ReportGenerator::loadServiceRecords(const std::string& filename) {
    serviceRecords.clear();
    std::ifstream ifs(filename);
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream ss(line);
        std::string currentDateTime, serviceDate, providerNumber, memberNumber, serviceCode, comments, feeStr;
        
        std::getline(ss, currentDateTime, ',');
        std::getline(ss, serviceDate, ',');
        std::getline(ss, providerNumber, ',');
        std::getline(ss, memberNumber, ',');
        std::getline(ss, serviceCode, ',');
        std::getline(ss, comments, ',');
        std::getline(ss, feeStr, ',');
        
        try {
            double fee = std::stod(feeStr);
            serviceRecords.emplace_back(currentDateTime, serviceDate, providerNumber, 
                                      memberNumber, serviceCode, comments, fee);
        } catch (...) {
            // Skip invalid lines
        }
    }
    std::cout << "Loaded " << serviceRecords.size() << " service records from " << filename << std::endl;
}

// Add a new service record
void ReportGenerator::addServiceRecord(const std::string& serviceDate, const std::string& providerNumber,
                                     const std::string& memberNumber, const std::string& serviceCode,
                                     const std::string& comments) {
    if (!serviceExists(serviceCode)) {
        throw std::invalid_argument("Service code does not exist: " + serviceCode);
    }
    
    double fee = serviceDirectory[serviceCode].getFee();
    std::string currentDateTime = getCurrentDateTime();
    
    serviceRecords.emplace_back(currentDateTime, serviceDate, providerNumber, 
                              memberNumber, serviceCode, comments, fee);
}

// Save service records to file
void ReportGenerator::saveServiceRecords(const std::string& filename) const {
    std::ofstream ofs(filename);
    for (const auto& record : serviceRecords) {
        ofs << record.currentDateTime << ","
            << record.serviceDate << ","
            << record.providerNumber << ","
            << record.memberNumber << ","
            << record.serviceCode << ","
            << record.comments << ","
            << record.fee << std::endl;
    }
    std::cout << "Saved " << serviceRecords.size() << " service records to " << filename << std::endl;
}

// Generate member report
void ReportGenerator::generateMemberReport(const std::string& memberNumber) const {
    if (memberDirectory.find(memberNumber) == memberDirectory.end()) {
        std::cerr << "Error: Member " << memberNumber << " not found." << std::endl;
        return;
    }
    
    const Member& member = memberDirectory.at(memberNumber);
    auto memberServices = getServicesForMember(memberNumber);
    
    if (memberServices.empty()) {
        std::cout << "No services found for member " << memberNumber << std::endl;
        return;
    }
    
    std::ostringstream report;
    report << "MEMBER SERVICES REPORT\n";
    report << "======================\n\n";
    report << "Member Name: " << member.getName() << "\n";
    report << "Member Number: " << member.getNumber() << "\n";
    report << "Street Address: " << member.getStreetAddress() << "\n";
    report << "City: " << member.getCity() << "\n";
    report << "State: " << member.getState() << "\n";
    report << "Zip Code: " << member.getZipCode() << "\n\n";
    report << "Services Provided:\n";
    report << "------------------\n";
    
    for (const auto& service : memberServices) {
        report << "Date of Service: " << service.serviceDate << "\n";
        
        // Find provider name
        if (providerDirectory.find(service.providerNumber) != providerDirectory.end()) {
            report << "Provider Name: " << providerDirectory.at(service.providerNumber).getName() << "\n";
        }
        
        // Find service name
        if (serviceDirectory.find(service.serviceCode) != serviceDirectory.end()) {
            report << "Service Name: " << serviceDirectory.at(service.serviceCode).getName() << "\n";
        }
        
        report << "\n";
    }
    
    // Generate filename with member name and current date
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream filename;
    filename << member.getName() << "_" << std::put_time(&tm, "%m-%d-%Y") << ".txt";
    
    writeToFile(filename.str(), report.str());
}

// Generate provider report
void ReportGenerator::generateProviderReport(const std::string& providerNumber) const {
    if (providerDirectory.find(providerNumber) == providerDirectory.end()) {
        std::cerr << "Error: Provider " << providerNumber << " not found." << std::endl;
        return;
    }
    
    const Provider& provider = providerDirectory.at(providerNumber);
    auto providerServices = getServicesForProvider(providerNumber);
    
    if (providerServices.empty()) {
        std::cout << "No services found for provider " << providerNumber << std::endl;
        return;
    }
    
    std::ostringstream report;
    report << "PROVIDER SERVICES REPORT\n";
    report << "========================\n\n";
    report << "Provider Name: " << provider.getName() << "\n";
    report << "Provider Number: " << provider.getNumber() << "\n";
    report << "Street Address: " << provider.getStreetAddress() << "\n";
    report << "City: " << provider.getCity() << "\n";
    report << "State: " << provider.getState() << "\n";
    report << "Zip Code: " << provider.getZipCode() << "\n\n";
    report << "Services Provided:\n";
    report << "------------------\n";
    
    double totalFee = 0.0;
    int consultationCount = 0;
    
    for (const auto& service : providerServices) {
        report << "Date of Service: " << service.serviceDate << "\n";
        report << "Date and Time Received: " << service.currentDateTime << "\n";
        
        // Find member name
        if (memberDirectory.find(service.memberNumber) != memberDirectory.end()) {
            report << "Member Name: " << memberDirectory.at(service.memberNumber).getName() << "\n";
        }
        
        report << "Member Number: " << service.memberNumber << "\n";
        report << "Service Code: " << service.serviceCode << "\n";
        report << "Fee: " << formatCurrency(service.fee) << "\n";
        
        if (!service.comments.empty()) {
            report << "Comments: " << service.comments << "\n";
        }
        
        report << "\n";
        
        totalFee += service.fee;
        consultationCount++;
    }
    
    report << "SUMMARY:\n";
    report << "--------\n";
    report << "Total Consultations: " << consultationCount << "\n";
    report << "Total Fee: " << formatCurrency(totalFee) << "\n";
    
    // Generate filename with provider name and current date
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream filename;
    filename << provider.getName() << "_" << std::put_time(&tm, "%m-%d-%Y") << ".txt";
    
    writeToFile(filename.str(), report.str());
}

// Generate summary report for manager
void ReportGenerator::generateSummaryReport() const {
    std::map<std::string, int> providerConsultations;
    std::map<std::string, double> providerFees;
    
    // Calculate totals per provider
    for (const auto& record : serviceRecords) {
        providerConsultations[record.providerNumber]++;
        providerFees[record.providerNumber] += record.fee;
    }
    
    std::ostringstream report;
    report << "SUMMARY REPORT FOR ACCOUNTS PAYABLE\n";
    report << "===================================\n\n";
    
    int totalProviders = 0;
    int totalConsultations = 0;
    double totalFees = 0.0;
    
    for (const auto& pair : providerConsultations) {
        const std::string& providerNumber = pair.first;
        int consultations = pair.second;
        double fee = providerFees[providerNumber];
        
        if (providerDirectory.find(providerNumber) != providerDirectory.end()) {
            const Provider& provider = providerDirectory.at(providerNumber);
            report << "Provider: " << provider.getName() << "\n";
            report << "Provider Number: " << providerNumber << "\n";
            report << "Consultations: " << consultations << "\n";
            report << "Fee: " << formatCurrency(fee) << "\n\n";
        }
        
        totalProviders++;
        totalConsultations += consultations;
        totalFees += fee;
    }
    
    report << "TOTALS:\n";
    report << "-------\n";
    report << "Total Providers: " << totalProviders << "\n";
    report << "Total Consultations: " << totalConsultations << "\n";
    report << "Total Fees: " << formatCurrency(totalFees) << "\n";
    
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream filename;
    filename << "Summary_Report_" << std::put_time(&tm, "%m-%d-%Y") << ".txt";
    
    writeToFile(filename.str(), report.str());
}

// Generate EFT report
void ReportGenerator::generateEFTReport() const {
    std::map<std::string, double> providerFees;
    
    // Calculate totals per provider
    for (const auto& record : serviceRecords) {
        providerFees[record.providerNumber] += record.fee;
    }
    
    std::ostringstream report;
    report << "ELECTRONIC FUNDS TRANSFER (EFT) DATA\n";
    report << "====================================\n\n";
    
    for (const auto& pair : providerFees) {
        const std::string& providerNumber = pair.first;
        double amount = pair.second;
        
        if (providerDirectory.find(providerNumber) != providerDirectory.end()) {
            const Provider& provider = providerDirectory.at(providerNumber);
            report << provider.getName() << "," << providerNumber << "," << std::fixed << std::setprecision(2) << amount << "\n";
        }
    }
    
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream filename;
    filename << "EFT_Data_" << std::put_time(&tm, "%m-%d-%Y") << ".txt";
    
    writeToFile(filename.str(), report.str());
}

// Generate provider directory
void ReportGenerator::generateProviderDirectory() const {
    std::vector<std::pair<std::string, Service>> sortedServices;
    
    for (const auto& pair : serviceDirectory) {
        sortedServices.push_back({pair.first, pair.second});
    }
    
    // Sort alphabetically by service name
    std::sort(sortedServices.begin(), sortedServices.end(),
              [](const std::pair<std::string, Service>& a, const std::pair<std::string, Service>& b) {
                  return a.second.getName() < b.second.getName();
              });
    
    std::ostringstream report;
    report << "PROVIDER DIRECTORY\n";
    report << "==================\n\n";
    report << "Service Name                 | Service Code | Fee\n";
    report << "-----------------------------------------------\n";
    
    for (const auto& pair : sortedServices) {
        const Service& service = pair.second;
        report << std::left << std::setw(28) << service.getName() 
               << " | " << std::setw(12) << service.getCode()
               << " | " << formatCurrency(service.getFee()) << "\n";
    }
    
    writeToFile("Provider_Directory.txt", report.str());
}

// Generate all weekly reports
void ReportGenerator::generateWeeklyReports() const {
    std::cout << "Generating weekly reports...\n" << std::endl;
    
    // Generate member reports for all members who received services
    std::set<std::string> membersWithServices;
    for (const auto& record : serviceRecords) {
        membersWithServices.insert(record.memberNumber);
    }
    
    for (const std::string& memberNumber : membersWithServices) {
        generateMemberReport(memberNumber);
    }
    
    // Generate provider reports for all providers who provided services
    std::set<std::string> providersWithServices;
    for (const auto& record : serviceRecords) {
        providersWithServices.insert(record.providerNumber);
    }
    
    for (const std::string& providerNumber : providersWithServices) {
        generateProviderReport(providerNumber);
    }
    
    // Generate summary and EFT reports
    generateSummaryReport();
    generateEFTReport();
    
    std::cout << "\nAll weekly reports generated successfully!" << std::endl;
}

// Interactive mode methods
void ReportGenerator::addMember(const Member& member) {
    memberDirectory[member.getNumber()] = member;
}

void ReportGenerator::addProvider(const Provider& provider) {
    providerDirectory[provider.getNumber()] = provider;
}

void ReportGenerator::addService(const Service& service) {
    serviceDirectory[service.getCode()] = service;
}

void ReportGenerator::updateMember(const std::string& memberNumber, const Member& updatedMember) {
    if (memberDirectory.find(memberNumber) != memberDirectory.end()) {
        memberDirectory[memberNumber] = updatedMember;
    }
}

void ReportGenerator::updateProvider(const std::string& providerNumber, const Provider& updatedProvider) {
    if (providerDirectory.find(providerNumber) != providerDirectory.end()) {
        providerDirectory[providerNumber] = updatedProvider;
    }
}

void ReportGenerator::removeMember(const std::string& memberNumber) {
    memberDirectory.erase(memberNumber);
}

void ReportGenerator::removeProvider(const std::string& providerNumber) {
    providerDirectory.erase(providerNumber);
}

// Validation methods
bool ReportGenerator::memberExists(const std::string& memberNumber) const {
    return memberDirectory.find(memberNumber) != memberDirectory.end();
}

bool ReportGenerator::providerExists(const std::string& providerNumber) const {
    return providerDirectory.find(providerNumber) != providerDirectory.end();
}

bool ReportGenerator::serviceExists(const std::string& serviceCode) const {
    return serviceDirectory.find(serviceCode) != serviceDirectory.end();
}

Service ReportGenerator::getService(const std::string& serviceCode) const {
    if (serviceExists(serviceCode)) {
        return serviceDirectory.at(serviceCode);
    }
    throw std::invalid_argument("Service code not found: " + serviceCode);
}

// Member card validation (replaces Member class static methods)
std::string ReportGenerator::validateMemberCard(const std::string& memberNumber) const {
    auto it = memberDirectory.find(memberNumber);
    if (it == memberDirectory.end()) {
        return "Invalid Member Number";
    }
    
    const Member& member = it->second;
    if (member.getIsSuspended()) {
        return "Member Suspended";
    }
    
    return "Validated";
}
