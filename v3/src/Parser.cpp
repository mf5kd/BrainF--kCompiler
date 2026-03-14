#include "../include/Parser.h"
#include <stdexcept>
#include <string>
#include <vector>

// Constructor
Parser::Parser(const std::vector<Token>& tokens) 
    : m_tokens(tokens), m_position(0) {
}

// Helper: Are we out of tokens?
bool Parser::isAtEnd() const {
    return m_position >= m_tokens.size() || peek().type == TokenType::EndOfFile;
}

// Helper: Look at the current token without consuming it
Token Parser::peek() const {
    return m_tokens[m_position];
}

// Helper: Consume the current token and move forward
Token Parser::advance() {
    if (!isAtEnd()) {
        m_position++;
    }
    return m_tokens[m_position - 1];
}

// Helper: Look at the token we just consumed (useful for error messages)
Token Parser::previous() const {
    return m_tokens[m_position - 1];
}

// Main logic: Kicks off the parsing process
std::vector<Instruction> Parser::parse() {
    std::vector<Instruction> program;

    while (!isAtEnd()) {
        Token token = advance();
        
        if (token.type == TokenType::SaveLoopTrigger) {
            if (isAtEnd() || peek().type != TokenType::LoopStart) {
                std::string errorMsg = "Syntax Error: Expected '[' after '*' at line " + std::to_string(token.line) + ", column " + std::to_string(token.column);
                throw std::runtime_error(errorMsg);
            }
            
            advance(); 
            std::vector<Instruction> savedLoopBody = parseLoop();
            program.push_back({TokenType::SaveLoopTrigger, savedLoopBody});

        } else if (token.type == TokenType::LoopStart) {
            // We hit a '['! 
            // 1. Call parseLoop() to gather everything inside this loop.
            std::vector<Instruction> pl = parseLoop();
            // 2. Create an Instruction with type LoopStart and the returned body. 
            // 3. Push it to 'program'.
            program.push_back({TokenType::LoopStart, pl});

        } else if (token.type == TokenType::LoopEnd) {
            // If we hit a ']' out here in the main parse loop, it means 
            // the user put a closing bracket without an opening bracket!
            // Throw a std::runtime_error using token.line and token.column.
            std::string errorMsg = "Syntax Error: Unmatched ']' at line " + std::to_string(token.line) + ", column " + std::to_string(token.column);
            
            throw std::runtime_error(errorMsg);

        } else if (token.type != TokenType::EndOfFile) {
            // It's a normal command (>, <, +, -, ., , or your ?)
            // Wrap it in an Instruction with an empty loopBody and add it to 'program'.
            program.push_back({token.type, {}});
        }
    }

    return program;
}

// Recursive logic: Gathers tokens until it finds the matching ']'
std::vector<Instruction> Parser::parseLoop() {
    std::vector<Instruction> loopBody;

    // Keep going until we hit the end of the file OR we peek a ']'
    while (!isAtEnd() && peek().type != TokenType::LoopEnd) {
        Token token = advance();

        if (token.type == TokenType::SaveLoopTrigger) {
            // Check for the mandatory '[' after '*'
            if (isAtEnd() || peek().type != TokenType::LoopStart) {
                std::string errorMsg = "Syntax Error: Expected '[' after '*' inside loop at line " + std::to_string(token.line) + ", column " + std::to_string(token.column);
                throw std::runtime_error(errorMsg);
            }

            advance(); // Consume the '['
            std::vector<Instruction> savedLoopBody = parseLoop(); // Recursively parse the body
            loopBody.push_back({TokenType::SaveLoopTrigger, savedLoopBody});
        
        } else if (token.type == TokenType::LoopStart) {
            // Brainfuck supports nested loops (loops inside loops)!
            // Recursively call parseLoop() here, just like you did in parse().
            std::vector<Instruction> pl = parseLoop();
            loopBody.push_back({TokenType::LoopStart, pl});
            
        } else if (token.type != TokenType::EndOfFile) {
            // It's a normal command inside the loop. Add it to loopBody.
            loopBody.push_back({token.type, {}});
        }
    }

    // If we exited because isAtEnd() is true, we never found the closing ']'!
    // Throw a std::runtime_error here complaining about an unclosed loop.
    if (isAtEnd()) {
        std::string errorMsg = "Syntax Error: Unmatched '[' at line " + std::to_string(peek().line) + ", column " + std::to_string(peek().column);
        throw std::runtime_error(errorMsg);
    }

    // If we made it here, peek().type MUST be a LoopEnd (']'). 
    // Consume it so we don't parse it again!
    if (!isAtEnd()) {
        advance(); 
    }

    return loopBody;
}
