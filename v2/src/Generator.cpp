#include "../include/Generator.h"
#include <sstream>

// Constructor
Generator::Generator(const std::vector<Instruction>& program)
    : m_program(program) {
}

// Main generation logic
std::string Generator::generate() {
    std::stringstream out;

    // a char array of size 30000 initialized to 0, and a char pointer.
    out << "// Auto-generated Brainfuck to C compiler output\n";
    // Add your C setup code to 'out' here
    out << "#include <stdio.h>\n";
    out << "int main() {\n";
    out << "    char tape[30000] = {0};\n";
    out << "    char *ptr = tape;\n";

                
    generateInstructions(m_program, out, 1);

    out << R"(    printf("\n");)" << "\n";
    out << "    return 0;\n}\n";

    return out.str();
}


// Recursive helper to handle the instructions and nested loops
void Generator::generateInstructions(const std::vector<Instruction>& instructions, std::stringstream& out, int indentLevel) {

    // Iterate over the instructions provided
    for (const auto& instr : instructions) {

        // Optional: Get the indent string to make the C code look pretty!
        std::string indent = getIndent(indentLevel);

        switch (instr.type) {
            case TokenType::IncrementPointer:
                out << indent << "ptr++;\n";
                break;
            case TokenType::DecrementPointer:
                out << indent << "ptr--;\n";
                break;
            case TokenType::IncrementValue:
                out << indent << "(*ptr)++;\n";
                break;
            case TokenType::DecrementValue:
                out << indent << "(*ptr)--;\n";
                break;
            case TokenType::Output:
                out << indent << "putchar(*ptr);\n";
                break;
            case TokenType::Input:
                out << indent << "*ptr = getchar();\n";
                break;
            case TokenType::PrintPosition:
                out << indent << R"(printf("%d", (int)(ptr - tape));)" << "\n";
                break;
            case TokenType::OutputAsNum:
                out << indent << "printf(\"%d\", *ptr);\n";
                break;
            case TokenType::InputAsNum:
                out << indent << "int temp; scanf(\"%d\", &temp); *ptr = temp;\n";
                break;
            case TokenType::LoopStart:
                out << indent << "while (*ptr) {\n";

                // Recursively generate the C code for everything inside 'instr.loopBody'
                generateInstructions(instr.loopBody, out, indentLevel + 1);

                out << indent << "}\n";
                break;
            default:
                break;
        }
    }
}

// Helper to generate spaces for pretty C code
std::string Generator::getIndent(int level) const {
    // Returns a string with 4 spaces for every indent level
    return std::string(level * 4, ' ');
}
