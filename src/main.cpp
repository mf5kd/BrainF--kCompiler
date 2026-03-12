#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../include/Lexer.h"
// Comment these out for now if you haven't created the header files yet!
// #include "../include/Parser.h" 
// #include "../include/Generator.h"

// helper function to make our enum class printable
std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IncrementPointer: return ">";
        case TokenType::DecrementPointer: return "<";
        case TokenType::IncrementValue:   return "+";
        case TokenType::DecrementValue:   return "-";
        case TokenType::Output:           return ".";
        case TokenType::Input:            return ",";
        case TokenType::LoopStart:        return "[";
        case TokenType::LoopEnd:          return "]";
        case TokenType::PrintPosition:    return "?";
        case TokenType::EndOfFile:        return "EOF";
        default:                          return "UNKNOWN";
    }
}

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

    // 3. Print out the tokens to verify the Lexer works!
    std::cout << "--- Lexer Output ---\n";
    for (const auto& token : tokens) {
        std::cout << "Token: " << tokenTypeToString(token.type) 
                  << "\t | Line: " << token.line 
                  << " | Col: " << token.column << "\n";
    }
    std::cout << "--------------------\n";

    return 0;
}
