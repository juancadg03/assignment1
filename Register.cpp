#include "Register.h"

// ==================== REGISTRO BASE ====================
Register::Register(string name) : value(0), name(name) {}

void Register::setValue(int val) {
    value = val;
}

int Register::getValue() const {
    return value;
}

void Register::display() const {
    cout << name << ": " << value << endl;
}

void Register::reset() {
    value = 0;
}

string Register::getName() const {
    return name;
}

// ==================== ACCUMULATOR ====================
Accumulator::Accumulator() : Register("ACC") {}

void Accumulator::display() const {
    cout << "Accumulator (ACC): " << value << endl;
}

// ==================== PROGRAM COUNTER ====================
ProgramCounter::ProgramCounter() : Register("PC") {}

void ProgramCounter::increment() {
    value++;
}

void ProgramCounter::display() const {
    cout << "Program Counter (PC): " << value << endl;
}

// ==================== INSTRUCTION REGISTER ====================
InstructionRegister::InstructionRegister() : Register("ICR") {}

void InstructionRegister::display() const {
    cout << "Instruction Register (ICR): " << value << endl;
}

// ==================== MEMORY ADDRESS REGISTER ====================
MemoryAddressRegister::MemoryAddressRegister() : Register("MAR") {}

void MemoryAddressRegister::display() const {
    cout << "Memory Address Register (MAR): " << value << endl;
}

// ==================== MEMORY DATA REGISTER ====================
MemoryDataRegister::MemoryDataRegister() : Register("MDR") {}

void MemoryDataRegister::display() const {
    cout << "Memory Data Register (MDR): " << value << endl;
}
