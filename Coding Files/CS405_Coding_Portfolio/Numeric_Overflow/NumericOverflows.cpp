// NumericOverflows.cpp
// Detects numeric overflow and underflow before the operation happens.

#include <iostream>
#include <limits>
#include <typeinfo>

template <typename T>
bool add_numbers(const T& start, const T& increment,
                 const unsigned long int& steps, T& result)
{
    result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        if (increment > std::numeric_limits<T>::max() - result)
        {
            return true;
        }

        result += increment;
    }

    return false;
}

template <typename T>
bool subtract_numbers(const T& start, const T& decrement,
                      const unsigned long int& steps, T& result)
{
    result = start;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        // In this exercise, underflow means the value would go below zero.
        if (decrement > result)
        {
            return true;
        }

        result -= decrement;
    }

    return false;
}

template <typename T>
void test_overflow()
{
    // START DO NOT CHANGE
    const unsigned long int steps = 5;
    const T increment = std::numeric_limits<T>::max() / steps;
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    T result{};

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", "
              << +increment << ", " << steps << ") = ";
    bool overflow = add_numbers<T>(start, increment, steps, result);
    if (overflow)
        std::cout << "Overflow detected" << std::endl;
    else
        std::cout << +result << std::endl;

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", "
              << +increment << ", " << (steps + 1) << ") = ";
    overflow = add_numbers<T>(start, increment, steps + 1, result);
    if (overflow)
        std::cout << "Overflow detected" << std::endl;
    else
        std::cout << +result << std::endl;
}

template <typename T>
void test_underflow()
{
    // START DO NOT CHANGE
    const unsigned long int steps = 5;
    const T decrement = std::numeric_limits<T>::max() / steps;
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    T result{};

    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", "
              << +decrement << ", " << steps << ") = ";
    bool underflow = subtract_numbers<T>(start, decrement, steps, result);
    if (underflow)
        std::cout << "Underflow detected" << std::endl;
    else
        std::cout << +result << std::endl;

    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", "
              << +decrement << ", " << (steps + 1) << ") = ";
    underflow = subtract_numbers<T>(start, decrement, steps + 1, result);
    if (underflow)
        std::cout << "Underflow detected" << std::endl;
    else
        std::cout << +result << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Underflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

int main()
{
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;
    do_overflow_tests(star_line);
    do_underflow_tests(star_line);
    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}
