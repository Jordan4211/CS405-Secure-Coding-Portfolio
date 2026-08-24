// Exceptions.cpp
// Demonstrates standard and custom exception handling.

#include <exception>
#include <iostream>
#include <stdexcept>

class CustomApplicationException : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "A custom application exception occurred.";
    }
};

bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic." << std::endl;
    throw std::runtime_error("Standard exception from application logic.");
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    try
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& error)
    {
        std::cout << "Caught standard exception: " << error.what() << std::endl;
    }

    std::cout << "Continuing after the standard exception." << std::endl;
    std::cout << "Leaving Custom Application Logic." << std::endl;

    throw CustomApplicationException();
}

float divide(float num, float den)
{
    if (den == 0.0f)
    {
        throw std::domain_error("Cannot divide by zero.");
    }

    return num / den;
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0.0f;

    try
    {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator
                  << ") = " << result << std::endl;
    }
    catch (const std::domain_error& error)
    {
        std::cout << "Division error: " << error.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    try
    {
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomApplicationException& error)
    {
        std::cout << "Caught custom exception: " << error.what() << std::endl;
    }
    catch (const std::exception& error)
    {
        std::cout << "Caught std::exception: " << error.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Caught an unknown exception." << std::endl;
    }

    return 0;
}
