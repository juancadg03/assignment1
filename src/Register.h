#ifndef REGISTER_H
#define REGISTER_H

class Register {
protected:
    int value;

public:
    Register();
    void setValue(int val);
    int getValue() const;
    void reset();
};

class Accumulator : public Register {
};

class ProgramCounter : public Register {
public:
    void increment();
};

class InstructionRegister : public Register {
};

class MemoryAddressRegister : public Register {
};

class MemoryDataRegister : public Register {
};

#endif
