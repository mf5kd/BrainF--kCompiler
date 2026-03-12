#pragma once
#include "Lexer.h"
#include <vector>

// Forward declaration if you decide to build an AST
struct ASTNode; 

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    
    // Returns a parsed structure (could be an AST or just validated tokens)
    void parse(); 

private:
    std::vector<Token> m_tokens;
    size_t m_position = 0;
};
