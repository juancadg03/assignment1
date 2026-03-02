#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

// ==================== REGISTRO BASE ====================
class Register {
protected:
    int value;
    string name;

public:
    Register(string name = "REG") : value(0), name(name) {}
    
    virtual void setValue(int val) {
        value = val;
    }
    
    virtual int getValue() const {
        return value;
    }
    
    virtual void display() const {
        cout << name << ": " << value << endl;
    }
    
    virtual void reset() {
        value = 0;
    }
    
    string getName() const {
        return name;
    }
};

// ==================== REGISTROS ESPECIALIZADOS ====================
class Accumulator : public Register {
public:
    Accumulator() : Register("ACC") {}
    
    void display() const override {
        cout << "Accumulator (ACC): " << value << endl;
    }
};

class ProgramCounter : public Register {
public:
    ProgramCounter() : Register("PC") {}
    
    void increment() {
        value++;
    }
    
    void display() const override {
        cout << "Program Counter (PC): " << value << endl;
    }
};

class InstructionRegister : public Register {
public:
    InstructionRegister() : Register("ICR") {}
    
    void display() const override {
        cout << "Instruction Register (ICR): " << value << endl;
    }
};

class MemoryAddressRegister : public Register {
public:
    MemoryAddressRegister() : Register("MAR") {}
    
    void display() const override {
        cout << "Memory Address Register (MAR): " << value << endl;
    }
};

class MemoryDataRegister : public Register {
public:
    MemoryDataRegister() : Register("MDR") {}
    
    void display() const override {
        cout << "Memory Data Register (MDR): " << value << endl;
    }
};

// ==================== UNIDAD DE CONTROL ====================
class ControlUnit {
private:
    enum State {
        FETCH,
        DECODE,
        EXECUTE,
        HALTED,
        PAUSED
    };
    
    State currentState;
    map<int, string> stateNames;

public:
    ControlUnit() : currentState(FETCH) {
        stateNames[FETCH] = "FETCH";
        stateNames[DECODE] = "DECODE";
        stateNames[EXECUTE] = "EXECUTE";
        stateNames[HALTED] = "HALTED";
        stateNames[PAUSED] = "PAUSED";
    }
    
    void setState(string state) {
        if (state == "FETCH") currentState = FETCH;
        else if (state == "DECODE") currentState = DECODE;
        else if (state == "EXECUTE") currentState = EXECUTE;
        else if (state == "HALTED") currentState = HALTED;
        else if (state == "PAUSED") currentState = PAUSED;
    }
    
    string getState() const {
        return stateNames.at(currentState);
    }
    
    void display() const {
        cout << "Control Unit (UC): " << getState() << endl;
    }
    
    bool isHalted() const {
        return currentState == HALTED;
    }
    
    bool isPaused() const {
        return currentState == PAUSED;
    }
    
    void reset() {
        currentState = FETCH;
    }
};

// ==================== ALU ====================
class ALU {
public:
    int add(int a, int b) {
        return a + b;
    }
    
    int increment(int a) {
        return a + 1;
    }
    
    int decrement(int a) {
        return a - 1;
    }
};

// ==================== MEMORIA PRINCIPAL ====================
class Memory {
private:
    static const int MEMORY_SIZE = 256;
    int data[MEMORY_SIZE];
    
public:
    Memory() {
        for (int i = 0; i < MEMORY_SIZE; i++) {
            data[i] = 0;
        }
    }
    
    void write(int address, int value) {
        if (address >= 0 && address < MEMORY_SIZE) {
            data[address] = value;
        } else {
            cout << "Error: Dirección de memoria fuera de rango: " << address << endl;
        }
    }
    
    int read(int address) const {
        if (address >= 0 && address < MEMORY_SIZE) {
            return data[address];
        } else {
            cout << "Error: Dirección de memoria fuera de rango: " << address << endl;
            return 0;
        }
    }
    
    void display() const {
        cout << "\n=== CONTENIDO DE MEMORIA ===" << endl;
        bool hasData = false;
        for (int i = 0; i < MEMORY_SIZE; i++) {
            if (data[i] != 0) {
                cout << "D" << i << ": " << data[i] << endl;
                hasData = true;
            }
        }
        if (!hasData) {
            cout << "(Memoria vacía)" << endl;
        }
    }
};

// ==================== ESTRUCTURA DE INSTRUCCIÓN ====================
struct Instruction {
    string opcode;
    string operand1;
    string operand2;
    string operand3;
    
    Instruction() : opcode(""), operand1("NULL"), operand2("NULL"), operand3("NULL") {}
};

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
    
    // Convertir dirección de memoria (ej: "D3" -> 3)
    int parseAddress(const string& addr) {
        if (addr.length() > 1 && addr[0] == 'D') {
            return stoi(addr.substr(1));
        }
        return -1;
    }
    
    // Verificar si es un valor inmediato
    bool isImmediate(const string& operand) {
        if (operand == "NULL" || operand.empty()) return false;
        // Verificar si es un número (puede ser negativo)
        try {
            stoi(operand);
            return true;
        } catch (...) {
            return false;
        }
    }
    
    // Obtener valor (inmediato o desde memoria)
    int getValue(const string& operand) {
        if (isImmediate(operand)) {
            return stoi(operand);
        } else if (operand[0] == 'D') {
            int addr = parseAddress(operand);
            return memory.read(addr);
        }
        return 0;
    }

public:
    CPU() : paused(false) {}
    
    // Cargar instrucciones desde archivo
    bool loadInstructions(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: No se pudo abrir el archivo " << filename << endl;
            return false;
        }
        
        instructions.clear();
        string line;
        
        while (getline(file, line)) {
            // Eliminar espacios en blanco al inicio y final
            size_t start = line.find_first_not_of(" \t\r\n");
            if (start == string::npos) continue; // Línea vacía o solo espacios
            
            size_t end = line.find_last_not_of(" \t\r\n");
            line = line.substr(start, end - start + 1);
            
            // Ignorar líneas vacías y comentarios
            if (line.empty() || line[0] == '#') continue;
            
            istringstream iss(line);
            Instruction inst;
            
            iss >> inst.opcode >> inst.operand1 >> inst.operand2 >> inst.operand3;
            
            instructions.push_back(inst);
            
            // Si es END, terminar de leer
            if (inst.opcode == "END") break;
        }
        
        file.close();
        return true;
    }
    
    // FASE 1: FETCH - Obtener instrucción
    void fetch() {
        cu.setState("FETCH");
        int pcValue = pc.getValue();
        
        if (pcValue < instructions.size()) {
            icr.setValue(pcValue);
            mar.setValue(pcValue);
        }
    }
    
    // FASE 2: DECODE - Decodificar instrucción
    void decode() {
        cu.setState("DECODE");
        // La decodificación se realiza implícitamente al obtener la instrucción
    }
    
    // FASE 3: EXECUTE - Ejecutar instrucción
    void execute() {
        cu.setState("EXECUTE");
        
        int pcValue = pc.getValue();
        if (pcValue >= instructions.size()) {
            cu.setState("HALTED");
            return;
        }
        
        Instruction& inst = instructions[pcValue];
        
        // Ejecutar según el opcode
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
        } else if (inst.opcode == "PAUSE") {
            executePAUSE(inst);
        } else if (inst.opcode == "END") {
            cu.setState("HALTED");
            return;
        } else {
            cout << "Error: Instrucción desconocida: " << inst.opcode << endl;
        }
        
        pc.increment();
    }
    
    // ==================== IMPLEMENTACIÓN DE INSTRUCCIONES ====================
    
    void executeSET(Instruction& inst) {
        // SET D1 X NULL NULL - Almacenar valor X en dirección D1
        int addr = parseAddress(inst.operand1);
        int value = getValue(inst.operand2);
        
        mar.setValue(addr);
        mdr.setValue(value);
        memory.write(addr, value);
    }
    
    void executeLDR(Instruction& inst) {
        // LDR D3 NULL NULL - Cargar valor de D3 en acumulador
        int addr = parseAddress(inst.operand1);
        mar.setValue(addr);
        
        int value = memory.read(addr);
        mdr.setValue(value);
        acc.setValue(value);
    }
    
    void executeADD(Instruction& inst) {
        // ADD D1 NULL NULL - Suma valor de D1 al acumulador
        // ADD D1 D3 NULL - Carga D1 en acumulador y suma D3
        // ADD D1 D3 D4 - Suma D1 + D3 y guarda en D4
        
        if (inst.operand2 == "NULL") {
            // ADD D1 NULL NULL
            int addr1 = parseAddress(inst.operand1);
            int value1 = memory.read(addr1);
            int result = alu.add(acc.getValue(), value1);
            acc.setValue(result);
            
        } else if (inst.operand3 == "NULL") {
            // ADD D1 D3 NULL
            int addr1 = parseAddress(inst.operand1);
            int addr2 = parseAddress(inst.operand2);
            int value1 = memory.read(addr1);
            int value2 = memory.read(addr2);
            acc.setValue(value1);
            int result = alu.add(value1, value2);
            acc.setValue(result);
            
        } else {
            // ADD D1 D3 D4
            int addr1 = parseAddress(inst.operand1);
            int addr2 = parseAddress(inst.operand2);
            int addr3 = parseAddress(inst.operand3);
            int value1 = memory.read(addr1);
            int value2 = memory.read(addr2);
            int result = alu.add(value1, value2);
            memory.write(addr3, result);
        }
    }
    
    void executeINC(Instruction& inst) {
        // INC D3 NULL NULL - Incrementar valor en D3
        int addr = parseAddress(inst.operand1);
        int value = memory.read(addr);
        int result = alu.increment(value);
        memory.write(addr, result);
    }
    
    void executeDEC(Instruction& inst) {
        // DEC D3 NULL NULL - Decrementar valor en D3
        int addr = parseAddress(inst.operand1);
        int value = memory.read(addr);
        int result = alu.decrement(value);
        memory.write(addr, result);
    }
    
    void executeSTR(Instruction& inst) {
        // STR D3 NULL NULL - Almacenar acumulador en D3
        int addr = parseAddress(inst.operand1);
        int value = acc.getValue();
        
        mar.setValue(addr);
        mdr.setValue(value);
        memory.write(addr, value);
    }
    
    void executeSHW(Instruction& inst) {
        // SHW D2 NULL NULL - Mostrar valor en D2
        // SHW ACC/ICR/MAR/MDR/UC - Mostrar registro específico
        
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
    
    void executePAUSE(Instruction& inst) {
        cu.setState("PAUSED");
        paused = true;
    }
    
    // ==================== EJECUCIÓN Y CONTROL ====================
    
    void run() {
        pc.reset();
        cu.reset();
        paused = false;
        
        while (!cu.isHalted()) {
            if (paused) {
                cin.ignore();
                cin.get();
                paused = false;
                cu.setState("FETCH");
            }
            
            fetch();
            decode();
            execute();
            
            if (cu.isHalted()) break;
        }
    }
    
    void displayStatus() {
        cout << "\n=== ESTADO DE REGISTROS ===" << endl;
        pc.display();
        icr.display();
        acc.display();
        mar.display();
        mdr.display();
        cu.display();
        memory.display();
        cout << "===========================" << endl;
    }
    
    void displayFinalStatus() {
        cout << "\n=== ESTADO FINAL ===" << endl;
        acc.display();
        memory.display();
        cout << "====================" << endl;
    }
};

// ==================== MAIN ====================
int main(int argc, char* argv[]) {
    CPU cpu;
    string filename;
    
    // Obtener nombre del archivo
    if (argc > 1) {
        filename = argv[1];
    } else {
        getline(cin, filename);
    }
    
    // Cargar y ejecutar instrucciones
    if (cpu.loadInstructions(filename)) {
        cpu.run();
    } else {
        return 1;
    }

    return 0;
}

