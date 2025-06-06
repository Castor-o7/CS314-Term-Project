#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "Member.h"
#include "Provider.h"
#include "Service.h"
#include <string>
#include <vector>
#include <map>
#include "googletest/include/gtest/gtest.h"

// Structure to represent a service record
struct ServiceRecord {
    std::string currentDateTime;    // MM-DD-YYYY HH:MM:SS
    std::string serviceDate;        // MM-DD-YYYY
    std::string providerNumber;     // 9 digits
    std::string memberNumber;       // 9 digits
    std::string serviceCode;        // 6 digits
    std::string comments;           // 100 characters (optional)
    double fee;                     // Service fee
    
    ServiceRecord(const std::string& currentDateTime, const std::string& serviceDate,
                  const std::string& providerNumber, const std::string& memberNumber,
                  const std::string& serviceCode, const std::string& comments, double fee)
        : currentDateTime(currentDateTime), serviceDate(serviceDate), providerNumber(providerNumber),
          memberNumber(memberNumber), serviceCode(serviceCode), comments(comments), fee(fee) {}
};

class ReportGenerator {
private:
    std::vector<ServiceRecord> serviceRecords;
    std::map<std::string, Service> serviceDirectory; // code -> Service
    std::map<std::string, Member> memberDirectory;   // number -> Member
    std::map<std::string, Provider> providerDirectory; // number -> Provider
    
    // Helper methods
    std::string getCurrentDateTime() const;
    std::string formatCurrency(double amount) const;
    void writeToFile(const std::string& filename, const std::string& content) const;
    std::vector<ServiceRecord> getServicesForMember(const std::string& memberNumber) const;
    std::vector<ServiceRecord> getServicesForProvider(const std::string& providerNumber) const;

public:
    // Constructor
    ReportGenerator();
    
    // Load data from files
    void loadMembers(const std::string& filename);
    void loadProviders(const std::string& filename);
    void loadServices(const std::string& filename);
    void loadServiceRecords(const std::string& filename);
    
    // Add service record (when a service is provided)
    void addServiceRecord(const std::string& serviceDate, const std::string& providerNumber,
                         const std::string& memberNumber, const std::string& serviceCode,
                         const std::string& comments = "");
    
    // Save service records to file
    void saveServiceRecords(const std::string& filename) const;
    
    // Report generation methods
    void generateMemberReport(const std::string& memberNumber) const;
    void generateProviderReport(const std::string& providerNumber) const;
    void generateSummaryReport() const;
    void generateEFTReport() const;
    void generateProviderDirectory() const;
    
    // Weekly report generation (generates all reports)
    void generateWeeklyReports() const;
    
    // Interactive mode methods
    void addMember(const Member& member);
    void addProvider(const Provider& provider);
    void addService(const Service& service);
    void updateMember(const std::string& memberNumber, const Member& updatedMember);
    void updateProvider(const std::string& providerNumber, const Provider& updatedProvider);
    void removeMember(const std::string& memberNumber);
    void removeProvider(const std::string& providerNumber);
    
    // Getters for validation
    bool memberExists(const std::string& memberNumber) const;
    bool providerExists(const std::string& providerNumber) const;
    bool serviceExists(const std::string& serviceCode) const;
    Service getService(const std::string& serviceCode) const;
    
    // Member validation (replaces static methods from Member class)
    std::string validateMemberCard(const std::string& memberNumber) const;
};

#endif // REPORTGENERATOR_H
