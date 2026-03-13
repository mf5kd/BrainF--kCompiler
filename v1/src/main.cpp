#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include "../include/Lexer.h"
#include "../include/Parser.h" 
#include "../include/Generator.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.bf>\n";
        return 1;
    }

    // 1. Read file safely into a string
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << "\n";
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string sourceCode = buffer.str();

    // 2. Pass to Lexer
    Lexer lexer(sourceCode);
    std::vector<Token> tokens = lexer.tokenize();
    
    std::vector<Instruction> ast;

    // 3. Pass tokens to Parser
    try {
        Parser parser(tokens);
        ast = parser.parse();
    } catch (const std::runtime_error& e) {
        // Catch those unmatched bracket errors
        std::cerr << "Compilation Failed!\n" << e.what() << "\n";
        return 1;
    }

    // 4. Pass AST to Generator
    Generator generator(ast);
    std::string cCode = generator.generate();

    // 5. Write the generated C code to a file
    std::string outputFilename = "output.c";
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file " << outputFilename << "\n";
        return 1;
    }
    
    outFile << cCode;
    outFile.close();
    
    std::string programName;
    std::string outputCommand;
    std::cout << "Enter Name of Program (or press Enter for default name = 'Program'):";
    std::getline(std::cin, programName);
    std::cout << std::endl;

    if (programName.empty()) {
        programName = "Program";
    }

    outputCommand = "gcc output.c -o output/" + programName;
    std::filesystem::create_directories("output");


    // 6. Compile the C code using GCC (Linux Debian)
    std::cout << "Compiling " << outputFilename << " with gcc...\n";
    
    // Execute the gcc command in the shell    
    int result = std::system(outputCommand.c_str());
    
    // Check if compilation was successful (system returns 0 on success)
    if (result == 0) {
        std::cout << "Successfully compiled! You can run it with: ./output/" + programName + "\n" << programName + " output: \n";
        std::system("rm output.c");
        std::system(("./output/" + programName).c_str());
    } else {
        std::cerr << "Error: GCC compilation failed. Make sure gcc is installed.\n";
        std::system("rm output.c");

        return 1;
    }

    return 0;
}
