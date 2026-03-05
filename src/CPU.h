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

class CPU {
private:

    Accumulator acc;
    ProgramCounter pc;
    InstructionRegister icr;
    MemoryAddressRegister mar;
    MemoryDataRegister mdr;
    ControlUnit cu;
    ALU alu;
    

    Memory memory;
    
    vector<Instruction> instructions;
    
    int parseAddress(const string& addr);
    int getValue(const string& operand);
    
    void executeSET(Instruction& inst);
    void executeLDR(Instruction& inst);
    void executeADD(Instruction& inst);
    void executeINC(Instruction& inst);
    void executeDEC(Instruction& inst);
    void executeSTR(Instruction& inst);
    void executeSHW(Instruction& inst);

public:
    CPU();
    
    bool loadInstructions(const string& filename);
    void fetch();
    void decode();
    void execute();
    void run();
};

#endif
