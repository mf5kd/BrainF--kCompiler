#include "../include/Generator.h"
#include <sstream>

// Constructor
Generator::Generator(const std::vector<Instruction>& program)
    : m_program(program) {
}

// Main generation logic
std::string Generator::generate() {
    std::stringstream out;

    // 1. Write the C boilerplate header
    // Hint: You'll need #include <stdio.h>, standard main function,
    // a char array of size 30000 initialized to 0, and a char pointer.
    out << "// Auto-generated Brainfuck to C compiler output\n";
    // Add your C setup code to 'out' here
    out << "#include <stdio.h>\n";
    out << "int main() {\n";
    out << "    char tape[30000] = {0};\n";
    out << "    char *ptr = tape;\n";

    // 2. Iterate over the AST and translate each Instruction to C code
    for (const auto& instr : m_program) {
        switch (instr.type) {
            case TokenType::IncrementPointer:
                // Output C code to move the pointer right
                out << "ptr++;\n";
                break;
            case TokenType::DecrementPointer:
                // Output C code to move the pointer left
                out << "ptr--;\n";
                break;
            case TokenType::IncrementValue:
                // Output C code to increment the current cell
                out << "(*ptr)++;\n";
                break;
            case TokenType::DecrementValue:
                // Output C code to decrement the current cell
                out << "(*ptr)--;\n";
                break;
            case TokenType::Output:
                // Output C code to print the current cell (e.g., putchar)
                out << "putchar(*ptr);\n";
                break;
            case TokenType::Input:
                // Output C code to read into the current cell (e.g., getchar)
                out << "*ptr = getchar();\n";
                break;
            case TokenType::LoopStart:
                // TODO: Output the start of a C 'while' loop.
                // Remember that a Brainfuck loop continues while the current cell is not 0.
                
                // TODO: Recursively generate the C code for everything inside 'instr.loopBody'
                
                // TODO: Output the closing brace '}' for the while loop
                break;
            default:
                break;
        }
    }

    // 3. Write the C boilerplate footer
    // Add 'return 0; }' to close out the C main function
    out << "return 0; }";

    return out.str();
}
