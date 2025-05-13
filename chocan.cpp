#include "member.cpp"


// Initialize the static memberValidationMap
std::unordered_map<std::string, bool> Member::memberValidationMap;

int main() {
    // Register member numbers
    Member::registerMemberNumber("123456789");
    Member::registerMemberNumber("987654321");

    // Validate member numbers
    std::cout << Member::validateMemberNumber("123456789") << std::endl; // Output: Validated
    std::cout << Member::validateMemberNumber("987654321") << std::endl; // Output: Validated

    // Create a new member
    Member member("John Doe", "123456789", "123 Main St", "Springfield", "IL", "62704", false);

    // Suspend the member
    member.suspend();
    std::cout << Member::validateMemberNumber("123456789") << std::endl; // Output: Member suspended

    // Reinstate the member
    member.reinstate();
    std::cout << Member::validateMemberNumber("123456789") << std::endl; // Output: Validated

    return 0;
}