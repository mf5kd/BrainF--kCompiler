// Lexer.h
#pragma once
#include <string>
#include <vector>
#include <string_view>

// Using an enum class is a modern C++ practice for strong scoping
enum class TokenType {
    IncrementPointer, // >
    DecrementPointer, // <
    IncrementValue,   // +
    DecrementValue,   // -
    Output,           // .
    Input,            // ,
    LoopStart,        // [
    LoopEnd,          // ]
    PrintPosition,    // ? (Your future custom command)
    EndOfFile
};

struct Token {
    TokenType type;
    int line;
    int column;
};

class Lexer {
public:
    explicit Lexer(std::string_view sourceCode);
    std::vector<Token> tokenize();

private:
    std::string_view m_source;
    size_t m_position = 0;
    int m_line = 1;
    int m_column = 1;
    
    bool isAtEnd() const;
    char advance();

    // Helper methods like advance(), peek(), etc.
};
