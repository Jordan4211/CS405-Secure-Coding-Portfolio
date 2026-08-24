// BufferOverflow.cpp
// Prevents input from overflowing the original 20-character buffer limit.

#include <iostream>
#include <string>

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    const std::string account_number = "CharlieBrown42";
    std::string user_input;

    std::cout << "Enter a value: ";
    std::getline(std::cin, user_input);

    // The old char array held 20 bytes, so only 19 characters were safe
    // after leaving room for the ending null character.
    if (user_input.length() >= 20)
    {
        std::cout << "Input is too long. Please enter fewer than 20 characters." << std::endl;
        std::cout << "Account Number = " << account_number << std::endl;
        return 1;
    }

    std::cout << "You entered: " << user_input << std::endl;
    std::cout << "Account Number = " << account_number << std::endl;

    return 0;
}
