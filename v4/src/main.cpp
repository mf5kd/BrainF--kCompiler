#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include <algorithm>
#include "../include/Lexer.h"
#include "../include/Parser.h" 
#include "../include/Generator.h"

// Helper function to trim whitespace and handle carriage returns (Windows line endings)
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file.txt>\n";
        std::cerr << "Config file format:\n";
        std::cerr << "  Line 1: Path to .bf file\n";
        std::cerr << "  Line 2: true/false (run after compilation)\n";
        std::cerr << "  Line 3: Output executable name\n";
        std::cerr << "  Line 4: true/false (keep generated C code file)\n";
        std::cerr << "  Line 5: Output C code file name\n";
        return 1;
    }

    // 1. Read the configuration file
    std::ifstream configFile(argv[1]);
    if (!configFile.is_open()) {
        std::cerr << "Error: Could not open config file " << argv[1] << "\n";
        return 1;
    }

    std::string bfFilePath, runFlagStr, programName, keepCFlagStr, cFileName;

    if (!std::getline(configFile, bfFilePath) ||
        !std::getline(configFile, runFlagStr) ||
        !std::getline(configFile, programName) ||
        !std::getline(configFile, keepCFlagStr) ||
        !std::getline(configFile, cFileName)) {
        std::cerr << "Error: Config file is missing required lines.\n";
        return 1;
    }

    // Clean up the parsed strings (removes \r if edited on Windows)
    bfFilePath = trim(bfFilePath);
    runFlagStr = trim(runFlagStr);
    programName = trim(programName);
    keepCFlagStr = trim(keepCFlagStr);
    cFileName = trim(cFileName);

    // Convert string to lower case for easy boolean checking
    std::transform(runFlagStr.begin(), runFlagStr.end(), runFlagStr.begin(), ::tolower);
    bool runAfterCompile = (runFlagStr == "true" || runFlagStr == "1");

    std::transform(keepCFlagStr.begin(), keepCFlagStr.end(), keepCFlagStr.begin(), ::tolower);
    bool keepCCode = (keepCFlagStr == "true" || keepCFlagStr == "1");

    if (programName.empty()) {
        programName = "Program";
    }
    
    if (cFileName.empty()) {
        cFileName = "output.c"; // Default fallback
    }

    // 2. Read the Brainfuck file safely into a string
    std::ifstream file(bfFilePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open Brainfuck source file " << bfFilePath << "\n";
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sourceCode = buffer.str();

    // 3. Pass to Lexer
    Lexer lexer(sourceCode);
    std::vector<Token> tokens = lexer.tokenize();
    
    std::vector<Instruction> ast;

    // 4. Pass tokens to Parser
    try {
        Parser parser(tokens);
        ast = parser.parse();
    } catch (const std::runtime_error& e) {
        // Catch those unmatched bracket errors
        std::cerr << "Compilation Failed!\n" << e.what() << "\n";
        return 1;
    }

    // 5. Pass AST to Generator
    Generator generator(ast);
    std::string cCode = generator.generate();

    // 6. Write the generated C code to a file
    std::ofstream outFile(cFileName);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file " << cFileName << "\n";
        return 1;
    }
    
    outFile << cCode;
    outFile.close();

    std::string outputCommand = "gcc " + cFileName + " -o " + programName;

    // 7. Compile the C code using GCC
    std::cout << "Compiling " << cFileName << " with gcc...\n";
    
    // Execute the gcc command in the shell    
    int result = std::system(outputCommand.c_str());
    
    // Check if compilation was successful (system returns 0 on success)
    if (result == 0) {
        if (!keepCCode) {
            std::system(("rm " + cFileName).c_str());
        } else {
            std::cout << "Generated C code saved as: " << cFileName << "\n";
        }
        
        std::cout << "Successfully compiled! You can run it with: ./" << programName << "\n";
        
        if (runAfterCompile) {
            std::cout << "Running " << programName << "...\n";
            std::system(("./" + programName).c_str());
        }
    } else {
        std::cerr << "Error: GCC compilation failed. Make sure gcc is installed.\n";
        if (!keepCCode) {
            std::system(("rm " + cFileName).c_str());
        }
        return 1;
    }

    return 0;
}
