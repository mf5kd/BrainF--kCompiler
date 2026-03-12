#pragma once
#include <string>
#include <vector>

class Generator {
public:
    Generator();
    
    // Pass in your parsed data here
    std::string generateCode(/* Parsed Data */);
    
    // Utility to write the C string to a file and optionally call gcc
    bool writeToFileAndCompile(const std::string& cCode, const std::string& outputPath);

private:
    // Boilerplate C code for the start and end of the generated file
    std::string getCHeader();
    std::string getCFooter();
};
