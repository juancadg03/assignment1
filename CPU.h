#ifndef CPU_H
#define CPU_H

#include <string>
#include <vector>
#include "Register.h"
#include "ControlUnit.h"
#include "ALU.h"
#include "Memory.h"
#include "Instruction.h"

using namespace std;

// ==================== CPU ====================
class CPU {
private:
    // Registros
    Accumulator acc;
    ProgramCounter pc;
    InstructionRegister icr;
    MemoryAddressRegister mar;
    MemoryDataRegister mdr;
    ControlUnit cu;
    ALU alu;
    
    // Memoria
    Memory memory;
    
    // Instrucciones cargadas
    vector<Instruction> instructions;
    
    // Estado de pausa
    bool paused;
    
    // Métodos auxiliares
    int parseAddress(const string& addr);
    bool isImmediate(const string& operand);
    int getValue(const string& operand);
    
    // Métodos de ejecución de instrucciones
    void executeSET(Instruction& inst);
    void executeLDR(Instruction& inst);
    void executeADD(Instruction& inst);
    void executeINC(Instruction& inst);
    void executeDEC(Instruction& inst);
    void executeSTR(Instruction& inst);
    void executeSHW(Instruction& inst);
    void executePAUSE(Instruction& inst);

public:
    CPU();
    
    // Métodos públicos
    bool loadInstructions(const string& filename);
    void fetch();
    void decode();
    void execute();
    void run();
    void displayStatus();
    void displayFinalStatus();
};

#endif
