using System;

public class ChocAn
{
    public static void Main(string[] args)
    {
        // Register member numbers
        Member.RegisterMemberNumber("123456789");
        Member.RegisterMemberNumber("987654321");

        // Validate member numbers
        Console.WriteLine(Member.ValidateMemberNumber("123456789")); // Output: Validated
        Console.WriteLine(Member.ValidateMemberNumber("987654321")); // Output: Validated

        // Create a new member
        Member member = new Member("John Doe", "123456789", "123 Main St", "Springfield", "IL", "62704", false);

        // Suspend the member
        member.Suspend();
        Console.WriteLine(Member.ValidateMemberNumber("123456789")); // Output: Member suspended

        // Reinstate the member
        member.Reinstate();
        Console.WriteLine(Member.ValidateMemberNumber("123456789")); // Output: Validated
    }
}