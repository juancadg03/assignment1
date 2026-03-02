#include <iostream>
#include <string>
#include "CPU.h"

using namespace std;

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
    int exitCode = 0;
    if (cpu.loadInstructions(filename)) {
        cpu.run();
    } else {
        exitCode = 1;
    }

    return exitCode;
}
