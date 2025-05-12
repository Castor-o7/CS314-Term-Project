using System;
using System.Collections.Generic;

public class Member
{
    // Static dictionary to store member numbers and their validation status
    private static Dictionary<string, bool> memberValidationMap = new Dictionary<string, bool>();

    // Member properties
    public string Name { get; set; } // 25 characters
    public string Number { get; private set; } // 9 digits
    public string StreetAddress { get; set; } // 25 characters
    public string City { get; set; } // 14 characters
    public string State { get; set; } // 2 characters
    public string ZipCode { get; set; } // 5 digits
    public bool IsSuspended { get; private set; } // Tracks if the member is suspended

    // Constructor
    public Member(string name, string number, string streetAddress, string city, string state, string zipCode, bool isSuspended)
    {
        if (!ValidateNumber(number)) throw new ArgumentException("Number must be exactly 9 digits.");
        if (!ValidateState(state)) throw new ArgumentException("State must be exactly 2 characters.");
        if (!ValidateZipCode(zipCode)) throw new ArgumentException("ZipCode must be exactly 5 digits.");

        if (!memberValidationMap.ContainsKey(number))
        {
            throw new ArgumentException("Member number is not registered in the system.");
        }

        Name = name;
        Number = number;
        StreetAddress = streetAddress;
        City = city;
        State = state;
        ZipCode = zipCode;
        IsSuspended = isSuspended;

        // Update the validation map with the member's suspension status
        memberValidationMap[number] = !isSuspended;
    }

    // Update member details with validation
    public void UpdateDetails(string streetAddress, string city, string state, string zipCode)
    {
        if (!ValidateState(state)) throw new ArgumentException("State must be exactly 2 characters.");
        if (!ValidateZipCode(zipCode)) throw new ArgumentException("ZipCode must be exactly 5 digits.");

        StreetAddress = streetAddress;
        City = city;
        State = state;
        ZipCode = zipCode;
    }

    // Suspend the member
    public void Suspend()
    {
        IsSuspended = true;
        memberValidationMap[Number] = false; // Update the validation map
    }

    // Reinstate the member
    public void Reinstate()
    {
        IsSuspended = false;
        memberValidationMap[Number] = true; // Update the validation map
    }

    // Static method to register a new member number
    public static void RegisterMemberNumber(string number)
    {
        if (!ValidateNumber(number)) throw new ArgumentException("Number must be exactly 9 digits.");
        if (!memberValidationMap.ContainsKey(number))
        {
            memberValidationMap.Add(number, true); // Default to valid
        }
        else
        {
            throw new ArgumentException("Member number already exists.");
        }
    }

    // Static method to validate a member number
    public static string ValidateMemberNumber(string number)
    {
        if (memberValidationMap.ContainsKey(number))
        {
            return memberValidationMap[number] ? "Validated" : "Member suspended";
        }
        else
        {
            return "Invalid member number";
        }
    }

    // Validation methods
    private static bool ValidateNumber(string number)
    {
        return number.Length == 9 && long.TryParse(number, out _);
    }

    private static bool ValidateState(string state)
    {
        return state.Length == 2 && !string.IsNullOrWhiteSpace(state);
    }

    private static bool ValidateZipCode(string zipCode)
    {
        return zipCode.Length == 5 && int.TryParse(zipCode, out _);
    }
}
