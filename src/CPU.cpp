#include "CPU.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

CPU::CPU() {}

int CPU::parseAddress(const string& addr) {
    int result = -1;
    if (addr.length() > 1 && addr[0] == 'D') {
        result = stoi(addr.substr(1));
    }
    return result;
}

int CPU::getValue(const string& operand) {
    int result = 0;
    if (operand != "NULL" && !operand.empty()) {
        try {
            result = stoi(operand);
        } catch (...) {
            if (operand[0] == 'D') {
                int addr = parseAddress(operand);
                result = memory.read(addr);
            }
        }
    }
    return result;
}


bool CPU::loadInstructions(const string& filename) {
    bool success = false;
    ifstream file(filename);
    if (file.is_open()) {
        instructions.clear();
        string line;
        bool endFound = false;
        
        while (getline(file, line) && !endFound) {
            size_t start = line.find_first_not_of(" \t\r\n");
            if (start != string::npos) {
                size_t end = line.find_last_not_of(" \t\r\n");
                line = line.substr(start, end - start + 1);
                
                if (!line.empty() && line[0] != '#') {
                    istringstream iss(line);
                    Instruction inst;
                    
                    iss >> inst.opcode >> inst.operand1 >> inst.operand2 >> inst.operand3;
                    
                    instructions.push_back(inst);
                    
                    if (inst.opcode == "END") {
                        endFound = true;
                    }
                }
            }
        }
        
        file.close();
        success = true;
    } else {
        cout << "Error: No se pudo abrir el archivo " << filename << endl;
    }
    return success;
}


void CPU::fetch() {
    cu.setState("FETCH");
    int pcValue = pc.getValue();
    
    if (pcValue < instructions.size()) {
        icr.setValue(pcValue);
        mar.setValue(pcValue);
    }
}

void CPU::decode() {
    cu.setState("DECODE");
}

void CPU::execute() {
    cu.setState("EXECUTE");
    
    int pcValue = pc.getValue();
    if (pcValue >= instructions.size()) {
        cu.setState("HALTED");
    } else {
        Instruction& inst = instructions[pcValue];
        
        if (inst.opcode == "SET") {
            executeSET(inst);
        } else if (inst.opcode == "LDR") {
            executeLDR(inst);
        } else if (inst.opcode == "ADD") {
            executeADD(inst);
        } else if (inst.opcode == "INC") {
            executeINC(inst);
        } else if (inst.opcode == "DEC") {
            executeDEC(inst);
        } else if (inst.opcode == "STR") {
            executeSTR(inst);
        } else if (inst.opcode == "SHW") {
            executeSHW(inst);
        } else if (inst.opcode == "END") {
            cu.setState("HALTED");
        } else {
            cout << "Error: Instrucción desconocida: " << inst.opcode << endl;
        }
        
        if (!cu.isHalted()) {
            pc.increment();
        }
    }
}


void CPU::executeSET(Instruction& inst) {
    int addr = parseAddress(inst.operand1);
    int value = getValue(inst.operand2);
    
    mar.setValue(addr);
    mdr.setValue(value);
    memory.write(addr, value);
}

void CPU::executeLDR(Instruction& inst) {
    int addr = parseAddress(inst.operand1);
    mar.setValue(addr);
    
    int value = memory.read(addr);
    mdr.setValue(value);
    acc.setValue(value);
}

void CPU::executeADD(Instruction& inst) {
    if (inst.operand2 == "NULL") {
        int addr1 = parseAddress(inst.operand1);
        int value1 = memory.read(addr1);
        int result = alu.add(acc.getValue(), value1);
        acc.setValue(result);
        
    } else if (inst.operand3 == "NULL") {
        int addr1 = parseAddress(inst.operand1);
        int addr2 = parseAddress(inst.operand2);
        int value1 = memory.read(addr1);
        int value2 = memory.read(addr2);
        acc.setValue(value1);
        int result = alu.add(value1, value2);
        acc.setValue(result);
        
    } else {
        int addr1 = parseAddress(inst.operand1);
        int addr2 = parseAddress(inst.operand2);
        int addr3 = parseAddress(inst.operand3);
        int value1 = memory.read(addr1);
        int value2 = memory.read(addr2);
        int result = alu.add(value1, value2);
        memory.write(addr3, result);
    }
}

void CPU::executeINC(Instruction& inst) {
    int addr = parseAddress(inst.operand1);
    int value = memory.read(addr);
    int result = alu.increment(value);
    memory.write(addr, result);
}

void CPU::executeDEC(Instruction& inst) {
    int addr = parseAddress(inst.operand1);
    int value = memory.read(addr);
    int result = alu.decrement(value);
    memory.write(addr, result);
}

void CPU::executeSTR(Instruction& inst) {
    int addr = parseAddress(inst.operand1);
    int value = acc.getValue();
    
    mar.setValue(addr);
    mdr.setValue(value);
    memory.write(addr, value);
}

void CPU::executeSHW(Instruction& inst) {
    string target = inst.operand1;
    
    if (target == "ACC") {
        cout << acc.getValue() << endl;
    } else if (target == "ICR") {
        cout << icr.getValue() << endl;
    } else if (target == "MAR") {
        cout << mar.getValue() << endl;
    } else if (target == "MDR") {
        cout << mdr.getValue() << endl;
    } else if (target == "UC") {
        cout << cu.getState() << endl;
    } else if (target[0] == 'D') {
        int addr = parseAddress(target);
        int value = memory.read(addr);
        cout << value << endl;
    }
}

void CPU::run() {
    pc.reset();
    cu.reset();
    
    while (!cu.isHalted()) {
        fetch();
        decode();
        execute();
    }
}
