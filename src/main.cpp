#include <iostream>
#include <string>
#include "CPU.h"

using namespace std;

int main(int argc, char* argv[]) {
    CPU cpu;
    string filename;
    
    if (argc > 1) {
        filename = argv[1];
    } else {
        getline(cin, filename);
    }
    
    if (cpu.loadInstructions(filename)) {
        cpu.run();
    }

    return 0;
}
