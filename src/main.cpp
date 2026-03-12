#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Lexer.h"
#include "../include/Parser.h"
#include "../include/Generator.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.bf>\n";
        return 1;
    }

    // 1. Read file
    // 2. Pass to Lexer
    // 3. Pass tokens to Parser
    // 4. Pass parsed data to Generator
    // 5. Output C file and system() call to GCC

    std::cout << "Compilation pipeline stub initialized.\n";
    return 0;
}
