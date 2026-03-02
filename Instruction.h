#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

using namespace std;

// ==================== ESTRUCTURA DE INSTRUCCIÓN ====================
struct Instruction {
    string opcode;
    string operand1;
    string operand2;
    string operand3;
    
    Instruction() : opcode(""), operand1("NULL"), operand2("NULL"), operand3("NULL") {}
};

#endif
