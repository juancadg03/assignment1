#include "Memory.h"

Memory::Memory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        data[i] = 0;
    }
}

void Memory::write(int address, int value) {
    if (address >= 0 && address < MEMORY_SIZE) {
        data[address] = value;
    } else {
        cout << "Error: Dirección de memoria fuera de rango: " << address << endl;
    }
}

int Memory::read(int address) const {
    int result = 0;
    if (address >= 0 && address < MEMORY_SIZE) {
        result = data[address];
    } else {
        cout << "Error: Dirección de memoria fuera de rango: " << address << endl;
    }
    return result;
}

void Memory::display() const {
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
