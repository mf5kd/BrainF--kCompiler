#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include "Lexer.h" // Includes your TokenType and Token definitions

// This acts as our simple Abstract Syntax Tree (AST) node
struct Instruction {
    TokenType type;
    // If the type is LoopStart, this vector holds all instructions inside the loop!
    // If it's a normal command like '+', this vector stays empty.
    std::vector<Instruction> loopBody; 
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    
    // Turns the flat list of tokens into a structured list of Instructions
    std::vector<Instruction> parse();

private:
    std::vector<Token> m_tokens;
    size_t m_position = 0;

    // Helper functions for navigating the token stream
    bool isAtEnd() const;
    Token peek() const;
    Token advance();
    Token previous() const;

    // The core recursive function that makes parsing nested loops easy
    std::vector<Instruction> parseLoop();
};
