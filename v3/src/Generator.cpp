#include "../include/Generator.h"
#include <sstream>

// Constructor
Generator::Generator(const std::vector<Instruction>& program)
    : m_program(program) {
}

// Main generation logic
std::string Generator::generate() {
    std::stringstream finalOut;
    std::stringstream mainOut;

    finalOut << "// Auto-generated Brainfuck to C compiler output\n";
    finalOut << "#include <stdio.h>\n\n";
    finalOut << "char tape[30000] = {0};\n";
    finalOut << "char *ptr = tape;\n\n";
    
    finalOut << "typedef void (*LoopFunc)(void);\n";
    finalOut << "LoopFunc funcTape[256] = {NULL};\n\n";

    mainOut << "int main() {\n";

    generateInstructions(m_program, mainOut, 1);

    mainOut << "    printf(\"\\n\");\n";
    mainOut << "    return 0;\n}\n";

    finalOut << m_functionsOut.str() << "\n";
    finalOut << mainOut.str();

    return finalOut.str();
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
            case TokenType::SaveLoopTrigger: {
                std::string funcName = "saved_loop_" + std::to_string(m_funcCounter++);

                m_functionsOut << "void " << funcName << "() {\n";

                generateInstructions(instr.loopBody, m_functionsOut, 1);

                m_functionsOut << "}\n\n";

                out << indent << "funcTape[(unsigned char)(*ptr)] = " << funcName << ";\n";
                break;
            }
            case TokenType::RunLoop: {
                out << indent << "if (funcTape[(unsigned char)(*ptr)] != NULL) {\n";
                out << indent << "    funcTape[(unsigned char)(*ptr)]();\n";
                out << indent << "}\n";
                break;
            default:
                break;
           
            }
        }
    }
}


// Helper to generate spaces for pretty C code
std::string Generator::getIndent(int level) const {
    // Returns a string with 4 spaces for every indent level
    return std::string(level * 4, ' ');
}
