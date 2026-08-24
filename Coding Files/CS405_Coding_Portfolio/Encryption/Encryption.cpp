// Encryption.cpp : This file contains the 'main' function.
//

#include <cassert>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    const size_t key_length = key.length();
    const size_t source_length = source.length();

    assert(key_length > 0);
    assert(source_length > 0);

    std::string output = source;

    // Repeat the key when it is shorter than the file data.
    for (size_t i = 0; i < source_length; ++i)
    {
        output[i] = source[i] ^ key[i % key_length];
    }

    return output;
}

std::string read_file(const std::string& filename)
{
    std::ifstream input_file(filename, std::ios::binary);

    if (!input_file)
    {
        throw std::runtime_error("Could not open the input file.");
    }

    std::ostringstream file_text;
    file_text << input_file.rdbuf();

    return file_text.str();
}

std::string get_student_name(const std::string& data)
{
    const size_t newline_position = data.find('\n');

    if (newline_position == std::string::npos)
    {
        return data;
    }

    return data.substr(0, newline_position);
}

void save_data_file(
    const std::string& filename,
    const std::string& student_name,
    const std::string& key,
    const std::string& data)
{
    std::ofstream output_file(filename, std::ios::binary);

    if (!output_file)
    {
        throw std::runtime_error("Could not create the output file.");
    }

    const std::time_t current_time = std::time(nullptr);
    std::tm current_date{};

#ifdef _WIN32
    localtime_s(&current_date, &current_time);
#else
    localtime_r(&current_time, &current_date);
#endif

    // Save the required header before the file data.
    output_file << student_name << '\n';
    output_file << std::put_time(&current_date, "%Y-%m-%d") << '\n';
    output_file << key << '\n';
    output_file.write(data.data(), static_cast<std::streamsize>(data.size()));
}

int main()
{
    const std::string input_file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrytpteddatafile.txt";
    const std::string key = "password";

    std::cout << "Encryption Decryption Test!" << std::endl;

    try
    {
        const std::string source_data = read_file(input_file_name);
        const std::string student_name = get_student_name(source_data);

        const std::string encrypted_data =
            encrypt_decrypt(source_data, key);

        save_data_file(
            encrypted_file_name,
            student_name,
            key,
            encrypted_data);

        const std::string decrypted_data =
            encrypt_decrypt(encrypted_data, key);

        save_data_file(
            decrypted_file_name,
            student_name,
            key,
            decrypted_data);

        std::cout << "Read File: " << input_file_name << '\n';
        std::cout << "Encrypted To: " << encrypted_file_name << '\n';
        std::cout << "Decrypted To: " << decrypted_file_name << '\n';
    }
    catch (const std::exception& error)
    {
        std::cout << "Error: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}
