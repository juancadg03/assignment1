#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
    static const int MEMORY_SIZE = 256;
    int data[MEMORY_SIZE];
    
public:
    Memory();
    void write(int address, int value);
    int read(int address) const;
};

#endif
