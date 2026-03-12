// Lexer.cpp
#include "../include/Lexer.h"

// Constructor: Initializes the lexer with the source code string
Lexer::Lexer(std::string_view sourceCode) 
    : m_source(sourceCode), m_position(0), m_line(1), m_column(1) {
}

// Helper: Checks if we've reached the end of the file
bool Lexer::isAtEnd() const {
    // Return true if m_position is greater than or equal to the length of m_source
    return this->m_position >= this->m_source.length();
}

// Helper: Consumes the current character and moves to the next one
char Lexer::advance() {
    // 1. Get the character at m_position
    char c = this->m_source[m_position];

    // 2. Increment m_position
    this->m_position += 1;

    // 3. Increment m_column
    this->m_column += 1;

    // 4. Return the character
    return c; 
}

// Main logic: Converts the whole string into a vector of tokens
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        // Grab the starting column/line for the current token before we advance
        int startColumn = m_column;
        int startLine = m_line;

        char c = advance();

        // Implement the logic to categorize 'c'
        switch (c) {
            case '>':
                tokens.push_back({TokenType::IncrementPointer, startLine, startColumn});
                break;
            case '<':
                tokens.push_back({TokenType::DecrementPointer, startLine, startColumn});
                break;
            case '+':
                tokens.push_back({TokenType::IncrementValue, startLine, startColumn});
                break;
            case '-':
                tokens.push_back({TokenType::DecrementValue, startLine, startColumn});
                break;
            case '.':
                tokens.push_back({TokenType::Output, startLine, startColumn});
                break;
            case ',':
                tokens.push_back({TokenType::Input, startLine, startColumn});
                break;
            case '[':
                tokens.push_back({TokenType::LoopStart, startLine, startColumn});
                break;
            case ']':
                tokens.push_back({TokenType::LoopEnd, startLine, startColumn});
                break;
        }

        // TODO (i want to wait for on this for later as i just want a nomal bf compiler) : Handle your custom '?' command here too! 

        // Handle Newlines ('\n')
        // If the character is a newline, you need to increment m_line and reset m_column to 1.
        if (c == '\n') {
            this->m_line += 1;
            this->m_column = 1;
        }

        // Note: For any other character (spaces, letters, etc.), you do nothing! 
        // Brainfuck treats unrecognized characters as comments, so just let the loop continue.
    }

    // Always good practice to append an EndOfFile token at the very end
    tokens.push_back({TokenType::EndOfFile, m_line, m_column});
    
    return tokens;
}
